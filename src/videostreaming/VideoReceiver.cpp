/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/


/**
 * @file
 *   @brief QGC Video Receiver
 *   @author Gus Grubba <gus@auterion.com>
 */

#include "VideoReceiver.h"

#include "VideoManager.h"

#include <QDebug>
#include <QUrl>
#include <QDir>
#include <QDateTime>
#include <QSysInfo>
#include <RovApplication.h>


#if defined(QGC_GST_STREAMING)

static const char* kVideoExtensions[] =
{
    "mkv",
    "mov",
    "mp4"
};

static const char* kVideoMuxes[] =
{
    "matroskamux",
    "qtmux",
    "mp4mux"
};

#define NUM_MUXES (sizeof(kVideoMuxes) / sizeof(char*))

#endif


VideoReceiver::VideoReceiver(QObject* parent)
    : QObject(parent)
#if defined(QGC_GST_STREAMING)
    , _running(false)
    , _recording(false)
    , _streaming(false)
    , _starting(false)
    , _stopping(false)
    , _stop(true)
    , _sink(nullptr)
    , _tee(nullptr)
    , _pipeline(nullptr)
    , _videoSink(nullptr)
    , _lastFrameId(G_MAXUINT64)
    , _lastFrameTime(0)
    , _restart_time_ms(1389)
    , _socket(nullptr)
    , _serverPresent(false)
    , _tcpTestInterval_ms(5000)
    , _udpReconnect_us(5000000)
#endif
    , _videoRunning(false)
    , _showFullScreen(false)
    , _videoSettings(nullptr)
{
//    _videoSettings = qgcApp()->toolbox()->settingsManager()->videoSettings();
#if defined(QGC_GST_STREAMING)
    _restart_timer.setSingleShot(true);
    connect(&_restart_timer, &QTimer::timeout, this, &VideoReceiver::_restart_timeout);
    //_restart_timer.start();
    _tcp_timer.setSingleShot(true);
    connect(&_tcp_timer, &QTimer::timeout, this, &VideoReceiver::_tcp_timeout);
    //connect(this, &VideoReceiver::msgErrorReceived, this, &VideoReceiver::_handleError);
    connect(this, &VideoReceiver::msgEOSReceived, this, &VideoReceiver::_handleEOS);
    connect(this, &VideoReceiver::msgStateChangedReceived, this, &VideoReceiver::_handleStateChanged);
    connect(&_frameTimer, &QTimer::timeout, this, &VideoReceiver::_updateTimer);

    connect(this, &VideoReceiver::recordingChanged, this, [=](){
        rovApp()->getToolbox()->getVideoManager()->recording = _recording;
    });

    _frameTimer.start(1000);
#endif
}

VideoReceiver::~VideoReceiver()
{
#if defined(QGC_GST_STREAMING)
    stop();
    setVideoSink(nullptr);
#endif
}

//-----------------------------------------------------------------------------
#if defined(QGC_GST_STREAMING)
static void
newPadCB(GstElement* element, GstPad* pad, gpointer data)
{
    gchar* name = gst_pad_get_name(pad);
    //g_print("A new pad %s was created\n", name);
    GstCaps* p_caps = gst_pad_get_pad_template_caps (pad);
    gchar* description = gst_caps_to_string(p_caps);
    qDebug()  << p_caps << ", " << description;
    g_free(description);
    GstElement* sink = GST_ELEMENT(data);
    if(gst_element_link_pads(element, name, sink, "sink") == false)
        qCritical() << "Failed to link elements\n";
    g_free(name);
}

static gboolean
autoplugQueryCaps(GstElement* bin, GstPad* pad, GstElement* element, GstQuery* query, gpointer data)
{
    GstElement* glupload = (GstElement* )data;

    GstPad* sinkpad = gst_element_get_static_pad(glupload, "sink");

    if (!sinkpad) {
        qCritical() << "No sink pad found";
        return FALSE;
    }

    GstCaps* filter;

    gst_query_parse_caps(query, &filter);

    GstCaps* sinkcaps = gst_pad_query_caps(sinkpad, filter);

    gst_query_set_caps_result(query, sinkcaps);

    const gboolean ret = !gst_caps_is_empty(sinkcaps);

    gst_caps_unref(sinkcaps);
    sinkcaps = nullptr;

    gst_object_unref(sinkpad);
    sinkpad = nullptr;

    return ret;
}

static gboolean
autoplugQueryContext(GstElement* bin, GstPad* pad, GstElement* element, GstQuery* query, gpointer data)
{
    GstElement* glsink = (GstElement* )data;

    GstPad* sinkpad = gst_element_get_static_pad(glsink, "sink");

    if (!sinkpad){
        qCritical() << "No sink pad found";
        return FALSE;
    }

    const gboolean ret = gst_pad_query(sinkpad, query);

    gst_object_unref(sinkpad);
    sinkpad = nullptr;

    return ret;
}

static gboolean
autoplugQueryCB(GstElement* bin, GstPad* pad, GstElement* element, GstQuery* query, gpointer data)
{
    gboolean ret;

    switch (GST_QUERY_TYPE (query)) {
    case GST_QUERY_CAPS:
        ret = autoplugQueryCaps(bin, pad, element, query, data);
        break;
    case GST_QUERY_CONTEXT:
        ret = autoplugQueryContext(bin, pad, element, query, data);
        break;
    default:
        ret = FALSE;
        break;
    }

    return ret;
}

//-----------------------------------------------------------------------------
static void
_wrapWithGhostPad(GstElement* element, GstPad* pad, gpointer data)
{
    gchar* name = gst_pad_get_name(pad);

    GstPad* ghostpad = gst_ghost_pad_new(name, pad);

    g_free(name);

    gst_pad_set_active(ghostpad, TRUE);

    if (!gst_element_add_pad(GST_ELEMENT_PARENT(element), ghostpad)) {
        qCritical() << "Failed to add ghost pad to source";
    }
}

static void
_linkPadWithOptionalBuffer(GstElement* element, GstPad* pad, gpointer data)
{
    gboolean isRtpPad = FALSE;

    GstCaps* filter = gst_caps_from_string("application/x-rtp");

    if (filter != nullptr) {
        GstCaps* caps = gst_pad_query_caps(pad, nullptr);

        if (caps != nullptr) {
            if (!gst_caps_is_any(caps) && gst_caps_can_intersect(caps, filter)) {
                isRtpPad = TRUE;
            }
            gst_caps_unref(caps);
            caps = nullptr;
        }

        gst_caps_unref(filter);
        filter = nullptr;
    }

    if (isRtpPad) {
        GstElement* buffer;

        if ((buffer = gst_element_factory_make("rtpjitterbuffer", nullptr)) != nullptr) {
            gst_bin_add(GST_BIN(GST_ELEMENT_PARENT(element)), buffer);

            gst_element_sync_state_with_parent(buffer);

            GstPad* sinkpad = gst_element_get_static_pad(buffer, "sink");

            if (sinkpad != nullptr) {
                const GstPadLinkReturn ret = gst_pad_link(pad, sinkpad);

                gst_object_unref(sinkpad);
                sinkpad = nullptr;

                if (ret == GST_PAD_LINK_OK) {
                    pad = gst_element_get_static_pad(buffer, "src");
                    element = buffer;
                } else {
                    qDebug()  << "Partially failed - gst_pad_link()";
                }
            } else {
                qDebug()  << "Partially failed - gst_element_get_static_pad()";
            }
        } else {
            qDebug()  << "Partially failed - gst_element_factory_make('rtpjitterbuffer')";
        }
    }

    newPadCB(element, pad, data);
}

static gboolean
_padProbe(GstElement* element, GstPad* pad, gpointer user_data)
{
    int* probeRes = (int*)user_data;

    *probeRes |= 1;

    GstCaps* filter = gst_caps_from_string("application/x-rtp");

    if (filter != nullptr) {
        GstCaps* caps = gst_pad_query_caps(pad, nullptr);

        if (caps != nullptr) {
            if (!gst_caps_is_any(caps) && gst_caps_can_intersect(caps, filter)) {
                *probeRes |= 2;
            }

            gst_caps_unref(caps);
            caps = nullptr;
        }

        gst_caps_unref(filter);
        filter = nullptr;
    }

    return TRUE;
}

static gboolean
_filterParserCaps(GstElement* bin, GstPad* pad, GstElement* element, GstQuery* query, gpointer data)
{
    Q_UNUSED(bin)
    Q_UNUSED(pad)
    Q_UNUSED(element)
    Q_UNUSED(data)

    if (GST_QUERY_TYPE(query) != GST_QUERY_CAPS) {
        return FALSE;
    }

    GstCaps* srcCaps;

    gst_query_parse_caps(query, &srcCaps);

    if (srcCaps == nullptr || gst_caps_is_any(srcCaps)) {
        return FALSE;
    }

    GstCaps* sinkCaps = nullptr;

    GstCaps* filter;

    if (sinkCaps == nullptr && (filter = gst_caps_from_string("video/x-h264")) != nullptr) {
        if (gst_caps_can_intersect(srcCaps, filter)) {
            sinkCaps = gst_caps_from_string("video/x-h264,stream-format=avc");
        }

        gst_caps_unref(filter);
        filter = nullptr;
    } else if (sinkCaps == nullptr && (filter = gst_caps_from_string("video/x-h265")) != nullptr) {
        if (gst_caps_can_intersect(srcCaps, filter)) {
            sinkCaps = gst_caps_from_string("video/x-h265,stream-format=hvc1");
        }

        gst_caps_unref(filter);
        filter = nullptr;
    }

    if (sinkCaps == nullptr) {
        return FALSE;
    }

    gst_query_set_caps_result(query, sinkCaps);

    gst_caps_unref(sinkCaps);
    sinkCaps = nullptr;

    return TRUE;
}

GstElement*
VideoReceiver::_makeSource(const QString& uri)
{
    if (uri.isEmpty()) {
        qCritical() << "Failed because URI is not specified";
        return nullptr;
    }

    bool isTaisync  = uri.contains("tsusb://");
    bool isUdp264   = uri.contains("udp://");
    bool isRtsp     = uri.contains("rtsp://");
    bool isUdp265   = uri.contains("udp265://");
    bool isTcpMPEGTS= uri.contains("tcp://");
    bool isUdpMPEGTS= uri.contains("mpegts://");

    GstElement* source  = nullptr;
    GstElement* buffer  = nullptr;
    GstElement* tsdemux = nullptr;
    GstElement* parser  = nullptr;
    GstElement* bin     = nullptr;
    GstElement* srcbin  = nullptr;

    do {
        QUrl url(uri);
        qDebug()<<uri;
        if(isTcpMPEGTS) {
            if ((source = gst_element_factory_make("tcpclientsrc", "source")) != nullptr) {
                g_object_set(static_cast<gpointer>(source), "host", qPrintable(url.host()), "port", url.port(), nullptr);
            }
        } else if (isRtsp) {
            if ((source = gst_element_factory_make("rtspsrc", "source")) != nullptr) {
                g_object_set(static_cast<gpointer>(source), "location", qPrintable(uri), "latency", 17, "udp-reconnect", 1, "timeout", _udpReconnect_us, NULL);
            }
        } else if(isUdp264 || isUdp265 || isUdpMPEGTS || isTaisync) {
            if ((source = gst_element_factory_make("udpsrc", "source")) != nullptr) {
                g_object_set(static_cast<gpointer>(source), "uri", QString("udp://%1:%2").arg(qPrintable(url.host()), QString::number(url.port())).toUtf8().data(), nullptr);

                GstCaps* caps = nullptr;

                if(isUdp264) {
                    if ((caps = gst_caps_from_string("application/x-rtp, media=(string)video, clock-rate=(int)90000, encoding-name=(string)H264")) == nullptr) {
                        qCritical() << "gst_caps_from_string() failed";
                        break;
                    }
                } else if (isUdp265) {
                    if ((caps = gst_caps_from_string("application/x-rtp, media=(string)video, clock-rate=(int)90000, encoding-name=(string)H265")) == nullptr) {
                        qCritical() << "gst_caps_from_string() failed";
                        break;
                    }
                }

                if (caps != nullptr) {
                    g_object_set(static_cast<gpointer>(source), "caps", caps, nullptr);
                    gst_caps_unref(caps);
                    caps = nullptr;
                }
            }
        } else {
            qDebug()  << "URI is not recognized";
        }

        if (!source) {
            qCritical() << "gst_element_factory_make() for data source failed";
            break;
        }

        if ((bin = gst_bin_new("sourcebin")) == nullptr) {
            qCritical() << "gst_bin_new('sourcebin') failed";
            break;
        }

        if ((parser = gst_element_factory_make("parsebin", "parser")) == nullptr) {
            qCritical() << "gst_element_factory_make('parsebin') failed";
            break;
        }

        g_signal_connect(parser, "autoplug-query", G_CALLBACK(_filterParserCaps), nullptr);

        gst_bin_add_many(GST_BIN(bin), source, parser, nullptr);

        // FIXME: AV: Android does not determine MPEG2-TS via parsebin - have to explicitly state which demux to use
        // FIXME: AV: tsdemux handling is a bit ugly - let's try to find elegant solution for that later
        if (isTcpMPEGTS || isUdpMPEGTS) {
            if ((tsdemux = gst_element_factory_make("tsdemux", nullptr)) == nullptr) {
                qCritical() << "gst_element_factory_make('tsdemux') failed";
                break;
            }

            gst_bin_add(GST_BIN(bin), tsdemux);

            if (!gst_element_link(source, tsdemux)) {
                qCritical() << "gst_element_link() failed";
                break;
            }

            source = tsdemux;
            tsdemux = nullptr;
        }

        int probeRes = 0;

        gst_element_foreach_src_pad(source, _padProbe, &probeRes);

        if (probeRes & 1) {
            if (probeRes & 2) {
                if ((buffer = gst_element_factory_make("rtpjitterbuffer", nullptr)) == nullptr) {
                    qCritical() << "gst_element_factory_make('rtpjitterbuffer') failed";
                    break;
                }

                gst_bin_add(GST_BIN(bin), buffer);

                if (!gst_element_link_many(source, buffer, parser, nullptr)) {
                    qCritical() << "gst_element_link() failed";
                    break;
                }
            } else {
                if (!gst_element_link(source, parser)) {
                    qCritical() << "gst_element_link() failed";
                    break;
                }
            }
        } else {
//            if (_videoSettings->lowLatencyMode()->rawValue().toBool()) {
//                g_signal_connect(source, "pad-added", G_CALLBACK(newPadCB), parser);
//            } else {
                g_signal_connect(source, "pad-added", G_CALLBACK(_linkPadWithOptionalBuffer), parser);
//            }
        }

        g_signal_connect(parser, "pad-added", G_CALLBACK(_wrapWithGhostPad), nullptr);

        source = buffer = parser = nullptr;

        srcbin = bin;
        bin = nullptr;
    } while(0);

    if (bin != nullptr) {
        gst_object_unref(bin);
        bin = nullptr;
    }

    if (parser != nullptr) {
        gst_object_unref(parser);
        parser = nullptr;
    }

    if (tsdemux != nullptr) {
        gst_object_unref(tsdemux);
        tsdemux = nullptr;
    }

    if (buffer != nullptr) {
        gst_object_unref(buffer);
        buffer = nullptr;
    }

    if (source != nullptr) {
        gst_object_unref(source);
        source = nullptr;
    }

    return srcbin;
}

//-----------------------------------------------------------------------------
void
VideoReceiver::_restart_timeout()
{
    rovApp()->getToolbox()->getVideoManager()->restartVideos();
}
#endif

//-----------------------------------------------------------------------------
#if defined(QGC_GST_STREAMING)
void
VideoReceiver::_tcp_timeout()
{
    //-- If socket is live, we got no connection nor a socket error
    delete _socket;
    _socket = nullptr;
    bool enabled = true;
    if(enabled) {
        //-- RTSP will try to connect to the server. If it cannot connect,
        //   it will simply give up and never try again. Instead, we keep
        //   attempting a connection on this timer. Once a connection is
        //   found to be working, only then we actually start the stream.
        QUrl url(_uri);
        //-- If RTSP and no port is defined, set default RTSP port (554)
        if(_uri.contains("rtsp://") && url.port() <= 0) {
            url.setPort(554);
        }
        _socket = new QTcpSocket;
        QNetworkProxy tempProxy;
        tempProxy.setType(QNetworkProxy::DefaultProxy);
        _socket->setProxy(tempProxy);
        connect(_socket, static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error), this, &VideoReceiver::_socketError);
        connect(_socket, &QTcpSocket::connected, this, &VideoReceiver::_connected);
        _socket->connectToHost(url.host(), static_cast<uint16_t>(url.port()));
        _tcp_timer.start(_tcpTestInterval_ms);
    }
}
#endif

//-----------------------------------------------------------------------------
#if defined(QGC_GST_STREAMING)
void
VideoReceiver::_connected()
{
    //-- Server showed up. Now we start the stream.
    _tcp_timer.stop();
    _socket->deleteLater();
    _socket = nullptr;
    bool enabled = true;
    if(enabled) {
        _serverPresent = true;
        start();
    }
}
#endif

//-----------------------------------------------------------------------------
#if defined(QGC_GST_STREAMING)
void
VideoReceiver::_socketError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    _socket->deleteLater();
    _socket = nullptr;
    //-- Try again in a while
    bool enabled = true;
    if(enabled) {
        _tcp_timer.start(_tcpTestInterval_ms);
    }
}
#endif

//-----------------------------------------------------------------------------
// When we finish our pipeline will look like this:
//
//                                   +-->queue-->decoder-->_videosink
//                                   |
//    datasource-->demux-->parser-->tee
//                                   ^
//                                   |
//                                   +-Here we will later link elements for recording
void
VideoReceiver::start()
{
    bool streamEnabled = true;
    bool streamConfigured = true;

    if(!streamEnabled ||
       !streamConfigured) {
        qDebug()  << "Stream not enabled/configured";
        return;
    }

#if defined(QGC_GST_STREAMING)
    _stop = false;

    QString uri = _uri;
    qDebug() << uri;

    if (uri.isEmpty()) {
        qDebug()  << "Failed because URI is not specified";
        return;
    }

    bool isUdp  = _uri.contains("udp://");
    bool isRtsp = _uri.contains("rtsp://");

    if (_videoSink == nullptr) {
        qWarning() << "Failed because video sink is not set";
        return;
    }

    bool lowMode  = rovApp()->getToolbox()->getSettingManager()->isLowMode();
    g_object_set(_videoSink, "sync", !lowMode, NULL);

    if(_running) {
        qDebug()  << "Already running!";
        return;
    }

    _starting = true;

    _lastFrameId = G_MAXUINT64;
    _lastFrameTime = 0;

    bool running    = false;

    GstElement*     dataSource  = NULL;
    GstCaps*        caps        = NULL;
    GstElement*     demux       = NULL;
    GstElement*     parser      = NULL;
    GstElement*     queue       = NULL;
    GstElement*     decoder     = NULL;

    do {
        if ((_pipeline = gst_pipeline_new("receiver")) == nullptr) {
            qCritical() << "gst_pipeline_new() failed";
            break;
        }

        if(isUdp) {
            dataSource = gst_element_factory_make("udpsrc", "udp-source");
        } else {
            dataSource = gst_element_factory_make("rtspsrc", "rtsp-source");
        }
        if (!dataSource) {
            qCritical() << "VideoReceiver::start() failed. Error with data source for gst_element_factory_make()";
            break;
        }

        if(isUdp) {
            if ((caps = gst_caps_from_string("application/x-rtp, media=(string)video, clock-rate=(int)90000, encoding-name=(string)H264")) == NULL) {
                qCritical() << "VideoReceiver::start() failed. Error with gst_caps_from_string()";
                break;
            }
            g_object_set(G_OBJECT(dataSource), "uri", qPrintable(_uri), "caps", caps, NULL);
        } else {
            g_object_set(G_OBJECT(dataSource), "location", qPrintable(_uri), "latency", 17, "udp-reconnect", 1, "timeout", static_cast<guint64>(5000000), NULL);
        }

        if ((demux = gst_element_factory_make("rtph264depay", "rtp-h264-depacketizer")) == NULL) {
            qCritical() << "VideoReceiver::start() failed. Error with gst_element_factory_make('rtph264depay')";
            break;
        }

        if(!isUdp) {
            g_signal_connect(dataSource, "pad-added", G_CALLBACK(newPadCB), demux);
        }

        if ((parser = gst_element_factory_make("h264parse", "h264-parser")) == NULL) {
            qCritical() << "VideoReceiver::start() failed. Error with gst_element_factory_make('h264parse')";
            break;
        }

        if ((decoder = gst_element_factory_make("avdec_h264", "h264-decoder")) == NULL) {
            qCritical() << "VideoReceiver::start() failed. Error with gst_element_factory_make('avdec_h264')";
            break;
        }

        if((_tee = gst_element_factory_make("tee", nullptr)) == nullptr)  {
            qCritical() << "gst_element_factory_make('tee') failed";
            break;
        }

        if((queue = gst_element_factory_make("queue", nullptr)) == nullptr)  {
            // TODO: We may want to add queue2 max-size-buffers=1 to get lower latency
            //       We should compare gstreamer scripts to QGroundControl to determine the need
            qCritical() << "gst_element_factory_make('queue') failed";
            break;
        }

        gst_bin_add_many(GST_BIN(_pipeline), dataSource, demux, parser, _tee, queue, decoder, _videoSink, NULL);

        if(isUdp) {
            // Link the pipeline in front of the tee
            if(!gst_element_link_many(dataSource, demux, parser, _tee, queue, decoder, _videoSink, NULL)) {
                qCritical() << "Unable to link elements.";
                break;
            }
        } else {
            if(!gst_element_link_many(demux, parser, _tee, queue, decoder, _videoSink, NULL)) {
                qCritical() << "Unable to link elements.";
                break;
            }
        }

        dataSource = demux = parser = queue = decoder = NULL;

        GstBus* bus = NULL;

        if ((bus = gst_pipeline_get_bus(GST_PIPELINE(_pipeline))) != NULL) {
            gst_bus_enable_sync_message_emission(bus);
            g_signal_connect(bus, "sync-message", G_CALLBACK(_onBusMessage), this);
            gst_object_unref(bus);
            bus = NULL;
        }

        GST_DEBUG_BIN_TO_DOT_FILE(GST_BIN(_pipeline), GST_DEBUG_GRAPH_SHOW_ALL, "pipeline-paused");
        running = gst_element_set_state(_pipeline, GST_STATE_PLAYING) != GST_STATE_CHANGE_FAILURE;

    } while(0);

    if (caps != NULL) {
        gst_caps_unref(caps);
        caps = NULL;
    }


    if (!running) {
        if (decoder != NULL) {
            gst_object_unref(decoder);
            decoder = NULL;
        }

        if (parser != NULL) {
            gst_object_unref(parser);
            parser = NULL;
        }

        if (demux != NULL) {
            gst_object_unref(demux);
            demux = NULL;
        }

        if (dataSource != NULL) {
            gst_object_unref(dataSource);
            dataSource = NULL;
        }

        if (_tee != NULL) {
            gst_object_unref(_tee);
            dataSource = NULL;
        }

        if (queue != NULL) {
            gst_object_unref(queue);
            dataSource = NULL;
        }

        if (_pipeline != NULL) {
            gst_object_unref(_pipeline);
            _pipeline = NULL;
        }

        _running = false;
    } else {
        GST_DEBUG_BIN_TO_DOT_FILE(GST_BIN(_pipeline), GST_DEBUG_GRAPH_SHOW_ALL, "pipeline-playing");
        _running = true;
    }
    _starting = false;

#endif
}

//-----------------------------------------------------------------------------
void
VideoReceiver::stop()
{
#if defined(QGC_GST_STREAMING)
    _stop = true;
    qDebug()  << "Stopping";
    if(!_streaming) {
        _shutdownPipeline();
    } else if (_pipeline != nullptr && !_stopping) {
        gst_element_send_event(_pipeline, gst_event_new_eos());
        _stopping = true;
        GstBus* bus = gst_pipeline_get_bus(GST_PIPELINE(_pipeline));
        GstMessage* message = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, (GstMessageType)(GST_MESSAGE_EOS|GST_MESSAGE_ERROR));
        gst_object_unref(bus);
        if(GST_MESSAGE_TYPE(message) == GST_MESSAGE_ERROR) {
            _shutdownPipeline();
            qCritical() << "Error stopping pipeline!";
        } else if(GST_MESSAGE_TYPE(message) == GST_MESSAGE_EOS) {
            _handleEOS();
        }
        gst_message_unref(message);
    }
#endif
}

//-----------------------------------------------------------------------------
void
VideoReceiver::setUri(const QString & uri)
{
    _uri = uri;
}

//-----------------------------------------------------------------------------
#if defined(QGC_GST_STREAMING)
void
VideoReceiver::_shutdownPipeline() {
    if(!_pipeline) {
        qDebug()  << "No pipeline";
        return;
    }
    GstBus* bus = nullptr;
    if ((bus = gst_pipeline_get_bus(GST_PIPELINE(_pipeline))) != nullptr) {
        gst_bus_disable_sync_message_emission(bus);
        gst_object_unref(bus);
        bus = nullptr;
    }
    gst_element_set_state(_pipeline, GST_STATE_NULL);
    gst_bin_remove(GST_BIN(_pipeline), _videoSink);
    _tee = nullptr;
    gst_object_unref(_pipeline);
    _pipeline = nullptr;
    delete _sink;
    _sink = nullptr;
    _serverPresent = false;
    _streaming = false;
    _recording = false;
    _stopping = false;
    _running = false;
    emit recordingChanged();
}
#endif

//-----------------------------------------------------------------------------
#if defined(QGC_GST_STREAMING)
void
VideoReceiver::_handleError() {
    qDebug()  << "Gstreamer error!";
    stop();
    _restart_timer.start(_restart_time_ms);
}
#endif
#if defined(QGC_GST_STREAMING)
void
VideoReceiver::_detachRecordingBranch(GstPadProbeInfo* info)
{
    Q_UNUSED(info)

    // Also unlinks and unrefs
    gst_bin_remove_many(GST_BIN(_pipeline), _sink->queue, _sink->parse, _sink->mux, _sink->filesink, NULL);

    // Give tee its pad back
    gst_element_release_request_pad(_tee, _sink->teepad);
    gst_object_unref(_sink->teepad);

    // Create temporary pipeline
    _pipelineStopRec = gst_pipeline_new("pipeStopRec");

    // Put our elements from the recording branch into the temporary pipeline
    gst_bin_add_many(GST_BIN(_pipelineStopRec), _sink->queue, _sink->parse, _sink->mux, _sink->filesink, NULL);
    gst_element_link_many(_sink->queue, _sink->parse, _sink->mux, _sink->filesink, NULL);

    // Add handler for EOS event
    GstBus* bus = gst_pipeline_get_bus(GST_PIPELINE(_pipelineStopRec));
    gst_bus_enable_sync_message_emission(bus);
    g_signal_connect(bus, "sync-message", G_CALLBACK(_onBusMessage), this);
    gst_object_unref(bus);

    if(gst_element_set_state(_pipelineStopRec, GST_STATE_PLAYING) == GST_STATE_CHANGE_FAILURE) {
        qDebug() << "problem starting _pipelineStopRec";
    }

    // Send EOS at the beginning of the pipeline
    GstPad* sinkpad = gst_element_get_static_pad(_sink->queue, "sink");
    gst_pad_send_event(sinkpad, gst_event_new_eos());
    gst_object_unref(sinkpad);
    qDebug() << "Recording branch unlinked";
}
#endif
//-----------------------------------------------------------------------------
#if defined(QGC_GST_STREAMING)
void
VideoReceiver::_handleEOS() {
    if(_stopping) {
        if(_recording && _sink->removing) {
            _shutdownRecordingBranch();
        }
        _shutdownPipeline();
        qDebug()  << "Stopped";
    } else if(_recording && _sink->removing) {
        _shutdownRecordingBranch();
    } else {
        qWarning() << "Unexpected EOS!";
        _handleError();
    }
}
#endif

//-----------------------------------------------------------------------------
#if defined(QGC_GST_STREAMING)
void
VideoReceiver::_handleStateChanged() {
//    qDebug() << "_handleStateChanged()";
    if(_pipeline) {
        _streaming = GST_STATE(_pipeline) == GST_STATE_PLAYING;
        //qDebug()  << "State changed, _streaming:" << _streaming;
    }
}
#endif

//-----------------------------------------------------------------------------
#if defined(QGC_GST_STREAMING)
gboolean
VideoReceiver::_onBusMessage(GstBus* bus, GstMessage* msg, gpointer data)
{
//    qDebug() << "_onBusMessage()";
    Q_UNUSED(bus)
    Q_ASSERT(msg != nullptr && data != nullptr);
    VideoReceiver* pThis = (VideoReceiver*)data;

    switch(GST_MESSAGE_TYPE(msg)) {
    case(GST_MESSAGE_ERROR): {
        gchar* debug;
        GError* error;
        gst_message_parse_error(msg, &error, &debug);
        g_free(debug);
        qCritical() << error->message;
        g_error_free(error);
        pThis->msgErrorReceived();
    }
        break;
    case(GST_MESSAGE_EOS):
        pThis->msgEOSReceived();
        break;
    case(GST_MESSAGE_STATE_CHANGED):
        pThis->msgStateChangedReceived();
        break;
    case(GST_MESSAGE_ELEMENT): {
        const GstStructure *s = gst_message_get_structure (msg);

        if (gst_structure_has_name (s, "GstBinForwarded")) {
            GstMessage *forward_msg = NULL;
            gst_structure_get (s, "message", GST_TYPE_MESSAGE, &forward_msg, NULL);
            if (forward_msg != nullptr) {
                if (GST_MESSAGE_TYPE(forward_msg) == GST_MESSAGE_EOS) {
                    pThis->msgEOSReceived();
                }
                gst_message_unref(forward_msg);
                forward_msg = nullptr;
            }
        }
    }
        break;
    default:
        break;
    }

    return TRUE;
}
#endif

//-----------------------------------------------------------------------------
#if defined(QGC_GST_STREAMING)
void
VideoReceiver::_cleanupOldVideos()
{
    bool enableStorageLimit = true;
    QString saveVideoPath = QString("/video/");
    //-- Only perform cleanup if storage limit is enabled
    if(enableStorageLimit) {
        QString savePath = saveVideoPath;
        QDir videoDir = QDir(savePath);
        videoDir.setFilter(QDir::Files | QDir::Readable | QDir::NoSymLinks | QDir::Writable);
        videoDir.setSorting(QDir::Time);
        //-- All the movie extensions we support
        QStringList nameFilters;
        for(uint32_t i = 0; i < NUM_MUXES; i++) {
            nameFilters << QString("*.") + QString(kVideoExtensions[i]);
        }
        videoDir.setNameFilters(nameFilters);
        //-- get the list of videos stored
        QFileInfoList vidList = videoDir.entryInfoList();
        if(!vidList.isEmpty()) {
            uint64_t total   = 0;
            //-- Settings are stored using MB
            uint64_t maxSize = (1024 * 1024 * 1024);
            //-- Compute total used storage
            for(int i = 0; i < vidList.size(); i++) {
                total += vidList[i].size();
            }
            //-- Remove old movies until max size is satisfied.
            while(total >= maxSize && !vidList.isEmpty()) {
                total -= vidList.last().size();
                qDebug()  << "Removing old video file:" << vidList.last().filePath();
                QFile file (vidList.last().filePath());
                file.remove();
                vidList.removeLast();
            }
        }
    }
}
#endif

//-----------------------------------------------------------------------------
#if defined(QGC_GST_STREAMING)
void
VideoReceiver::setVideoSink(GstElement* videoSink)
{
    if(_pipeline != nullptr) {
        qDebug()  << "Video receiver pipeline is active, video sink change is not possible";
        return;
    }

    if (_videoSink != nullptr) {
        gst_object_unref(_videoSink);
        _videoSink = nullptr;
    }

    if (videoSink != nullptr) {
        _videoSink = videoSink;
        gst_object_ref(_videoSink);

        GstPad* pad = gst_element_get_static_pad(_videoSink, "sink");

        if (pad != nullptr) {
            gst_pad_add_probe(pad, (GstPadProbeType)(GST_PAD_PROBE_TYPE_BUFFER), _videoSinkProbe, this, nullptr);
            gst_object_unref(pad);
            pad = nullptr;
        } else {
            qCritical() << "Unable to find sink pad of video sink";
        }
    }
}
#endif

//-----------------------------------------------------------------------------
// When we finish our pipeline will look like this:
//
//                                   +-->queue-->decoder-->_videosink
//                                   |
//                         source-->tee
//                                   |
//                                   |    +---------_sink----------+
//                                   |    |                        |
//   we are adding these elements->  +->teepad-->queue-->_filesink |
//                                        |                        |
//                                        +------------------------+
#if defined(QGC_GST_STREAMING)
GstElement*
VideoReceiver::_makeFileSink(const QString& videoFile, unsigned format)
{
    GstElement* fileSink = nullptr;
    GstElement* mux = nullptr;
    GstElement* sink = nullptr;
    GstElement* bin = nullptr;
    bool releaseElements = true;

    do{
        if ((mux = gst_element_factory_make(kVideoMuxes[format], nullptr)) == nullptr) {
            qCritical() << "gst_element_factory_make('" << kVideoMuxes[format] << "') failed";
            break;
        }

        if ((sink = gst_element_factory_make("filesink", nullptr)) == nullptr) {
            qCritical() << "gst_element_factory_make('filesink') failed";
            break;
        }

        g_object_set(static_cast<gpointer>(sink), "location", qPrintable(videoFile), nullptr);

        if ((bin = gst_bin_new("sinkbin")) == nullptr) {
            qCritical() << "gst_bin_new('sinkbin') failed";
            break;
        }

        GstPadTemplate* padTemplate;

        if ((padTemplate = gst_element_class_get_pad_template(GST_ELEMENT_GET_CLASS(mux), "video_%u")) == nullptr) {
            qCritical() << "gst_element_class_get_pad_template(mux) failed";
            break;
        }

        // FIXME: AV: pad handling is potentially leaking (and other similar places too!)
        GstPad* pad;

        if ((pad = gst_element_request_pad(mux, padTemplate, nullptr, nullptr)) == nullptr) {
            qCritical() << "gst_element_request_pad(mux) failed";
            break;
        }

        gst_bin_add_many(GST_BIN(bin), mux, sink, nullptr);

        releaseElements = false;

        GstPad* ghostpad = gst_ghost_pad_new("sink", pad);

        gst_element_add_pad(bin, ghostpad);

        gst_object_unref(pad);
        pad = nullptr;

        if (!gst_element_link(mux, sink)) {
            qCritical() << "gst_element_link() failed";
            break;
        }

        fileSink = bin;
        bin = nullptr;
    } while(0);

    if (releaseElements) {
        if (sink != nullptr) {
            gst_object_unref(sink);
            sink = nullptr;
        }

        if (mux != nullptr) {
            gst_object_unref(mux);
            mux = nullptr;
        }
    }

    if (bin != nullptr) {
        gst_object_unref(bin);
        bin = nullptr;
    }

    return fileSink;
}
#endif

void
VideoReceiver::startRecording(void)
{
#if defined(QGC_GST_STREAMING)

    qDebug()  << "Starting recording";
    if( !_running ){
        return ;
    }
    // exit immediately if we are already recording
    if(_pipeline == nullptr || _recording) {
        qDebug()  << "Already recording!";
        return;
    }

    uint32_t muxIdx = 2;
    if(muxIdx >= NUM_MUXES) {
        qDebug() << "Invalid video format defined.";
//        qgcApp()->showMessage(tr("Invalid video format defined."));
        return;
    }


    QString savePath = rovApp()->getToolbox()->getSettingManager()->getVideoPath();

    if(savePath.isEmpty()) {
        qDebug() << "Unabled to record video. Video save path must be specified in Settings";
//        qgcApp()->showMessage(tr("Unabled to record video. Video save path must be specified in Settings."));
        return;
    }
    _sink           = new Sink();
    _sink->teepad   = gst_element_get_request_pad(_tee, "src_%u");
    _sink->queue    = gst_element_factory_make("queue", NULL);
    _sink->parse    = gst_element_factory_make("h264parse", NULL);
    _sink->mux      = gst_element_factory_make(kVideoMuxes[muxIdx], NULL);
    _sink->filesink = gst_element_factory_make("filesink", NULL);
    _sink->removing = false;

    if(!_sink->teepad || !_sink->queue || !_sink->mux || !_sink->filesink || !_sink->parse) {
        qCritical() << "VideoReceiver::startRecording() failed to make _sink elements";
        return;
    }

    QString videoFile;
    videoFile = savePath + "/" + QDateTime::currentDateTime().toString("yyyy-MM-dd_hh.mm.ss") + "." + kVideoExtensions[muxIdx];

    g_object_set(G_OBJECT(_sink->filesink), "location", qPrintable(videoFile), NULL);
    qDebug() << "New video file:" << videoFile;

    gst_object_ref(_sink->queue);
    gst_object_ref(_sink->parse);
    gst_object_ref(_sink->mux);
    gst_object_ref(_sink->filesink);

    gst_bin_add_many(GST_BIN(_pipeline), _sink->queue, _sink->parse, _sink->mux, _sink->filesink, NULL);
    gst_element_link_many(_sink->queue, _sink->parse, _sink->mux, _sink->filesink, NULL);

    gst_element_sync_state_with_parent(_sink->queue);
    gst_element_sync_state_with_parent(_sink->parse);
    gst_element_sync_state_with_parent(_sink->mux);
    gst_element_sync_state_with_parent(_sink->filesink);

    // Install a probe on the recording branch to drop buffers until we hit our first keyframe
    // When we hit our first keyframe, we can offset the timestamps appropriately according to the first keyframe time
    // This will ensure the first frame is a keyframe at t=0, and decoding can begin immediately on playback
    GstPad* probepad = gst_element_get_static_pad(_sink->queue, "src");
    gst_pad_add_probe(probepad, (GstPadProbeType)(GST_PAD_PROBE_TYPE_BUFFER /* | GST_PAD_PROBE_TYPE_BLOCK */), _keyframeWatch, this, NULL); // to drop the buffer or to block the buffer?
    gst_object_unref(probepad);

    // Link the recording branch to the pipeline
    GstPad* sinkpad = gst_element_get_static_pad(_sink->queue, "sink");
    gst_pad_link(_sink->teepad, sinkpad);
    gst_object_unref(sinkpad);

    GST_DEBUG_BIN_TO_DOT_FILE(GST_BIN(_pipeline), GST_DEBUG_GRAPH_SHOW_ALL, "pipeline-recording");

    _recording = true;

    emit recordingChanged();
    qDebug() << "Recording started";

#endif
}

//-----------------------------------------------------------------------------
void
VideoReceiver::stopRecording(void)
{
#if defined(QGC_GST_STREAMING)
    qDebug()  << "Stopping recording";
    if( !_running ){
        return ;
    }
    // exit immediately if we are not recording
    if(_pipeline == nullptr || !_recording) {
        qDebug()  << "Not recording!";
        return;
    }
    // Wait for data block before unlinking
    gst_pad_add_probe(_sink->teepad, GST_PAD_PROBE_TYPE_IDLE, _unlinkCallBack, this, nullptr);

    if(_recording == true){
        _recording = false;
        emit recordingChanged();
    }
#endif
}

//-----------------------------------------------------------------------------
// This is only installed on the transient _pipelineStopRec in order
// to finalize a video file. It is not used for the main _pipeline.
// -EOS has appeared on the bus of the temporary pipeline
// -At this point all of the recoring elements have been flushed, and the video file has been finalized
// -Now we can remove the temporary pipeline and its elements
#if defined(QGC_GST_STREAMING)
void
VideoReceiver::_shutdownRecordingBranch()
{
    gst_bin_remove(GST_BIN(_pipelineStopRec), _sink->queue);
    gst_bin_remove(GST_BIN(_pipelineStopRec), _sink->parse);
    gst_bin_remove(GST_BIN(_pipelineStopRec), _sink->mux);
    gst_bin_remove(GST_BIN(_pipelineStopRec), _sink->filesink);

    gst_element_set_state(_pipelineStopRec, GST_STATE_NULL);
    gst_object_unref(_pipelineStopRec);
    _pipelineStopRec = NULL;

    gst_element_set_state(_sink->filesink,  GST_STATE_NULL);
    gst_element_set_state(_sink->parse,     GST_STATE_NULL);
    gst_element_set_state(_sink->mux,       GST_STATE_NULL);
    gst_element_set_state(_sink->queue,     GST_STATE_NULL);

    gst_object_unref(_sink->queue);
    gst_object_unref(_sink->parse);
    gst_object_unref(_sink->mux);
    gst_object_unref(_sink->filesink);

    delete _sink;
    _sink = NULL;
    _recording = false;

    emit recordingChanged();
    qDebug()  << "Recording stopped";
}
#endif

//-----------------------------------------------------------------------------
// -Unlink the recording branch from the tee in the main _pipeline
// -Create a second temporary pipeline, and place the recording branch elements into that pipeline
// -Setup watch and handler for EOS event on the temporary pipeline's bus
// -Send an EOS event at the beginning of that pipeline
#if defined(QGC_GST_STREAMING)
void
VideoReceiver::_unlinkRecordingBranch(GstPadProbeInfo* info)
{
    Q_UNUSED(info)
    // Send EOS at the beginning of the pipeline
    GstPad* sinkpad = gst_element_get_static_pad(_sink->queue, "sink");
    gst_pad_unlink(_sink->teepad, sinkpad);
    gst_pad_send_event(sinkpad, gst_event_new_eos());
    gst_object_unref(sinkpad);
    qDebug()  << "Recording EOS was sent";
    // Give tee its pad back
    gst_element_release_request_pad(_tee, _sink->teepad);
    gst_object_unref(_sink->teepad);
}
#endif

//-----------------------------------------------------------------------------
#if defined(QGC_GST_STREAMING)
GstPadProbeReturn
VideoReceiver::_unlinkCallBack(GstPad* pad, GstPadProbeInfo* info, gpointer user_data)
{
    Q_UNUSED(pad);
    if(info != nullptr && user_data != nullptr) {
        VideoReceiver* pThis = static_cast<VideoReceiver*>(user_data);
        // We will only act once
        if(g_atomic_int_compare_and_exchange(&pThis->_sink->removing, FALSE, TRUE)) {
            pThis->_detachRecordingBranch(info);
        }
    }
    return GST_PAD_PROBE_REMOVE;
}
#endif

//-----------------------------------------------------------------------------
#if defined(QGC_GST_STREAMING)
GstPadProbeReturn
VideoReceiver::_videoSinkProbe(GstPad* pad, GstPadProbeInfo* info, gpointer user_data)
{
//    qDebug("VideoReceiver::VideoSinkProbe");
    Q_UNUSED(pad);
    if(info != nullptr && user_data != nullptr) {
//        qDebug() << "in if";
        VideoReceiver* pThis = static_cast<VideoReceiver*>(user_data);
        pThis->_noteVideoSinkFrame();
    }

//    qDebug("End Probe");
    return GST_PAD_PROBE_OK;
}
#endif

//-----------------------------------------------------------------------------
#if defined(QGC_GST_STREAMING)
void
VideoReceiver::_noteVideoSinkFrame()
{
    _lastFrameTime = QDateTime::currentSecsSinceEpoch();
}
#endif

//-----------------------------------------------------------------------------
#if defined(QGC_GST_STREAMING)
GstPadProbeReturn
VideoReceiver::_keyframeWatch(GstPad* pad, GstPadProbeInfo* info, gpointer user_data)
{
    qDebug() << "_keyframeWatch";
    Q_UNUSED(pad);
    if(info != nullptr && user_data != nullptr) {
        GstBuffer* buf = gst_pad_probe_info_get_buffer(info);
        if(GST_BUFFER_FLAG_IS_SET(buf, GST_BUFFER_FLAG_DELTA_UNIT)) { // wait for a keyframe
            return GST_PAD_PROBE_DROP;
        } else {
            VideoReceiver* pThis = static_cast<VideoReceiver*>(user_data);

            // set media file '0' offset to current timeline position - we don't want to touch other elements in the graph, except these which are downstream!
            gst_pad_set_offset(pad, -buf->pts);

            // Add the filesink once we have a valid I-frame
            gst_bin_add(GST_BIN(pThis->_pipeline), pThis->_sink->filesink);
            if (!gst_element_link(pThis->_sink->queue, pThis->_sink->filesink)) {
                qCritical() << "Failed to link queue and file sink";
            }
            gst_element_sync_state_with_parent(pThis->_sink->filesink);

            qDebug()  << "Got keyframe, stop dropping buffers";
            pThis->gotFirstRecordingKeyFrame();
        }
    }

    return GST_PAD_PROBE_REMOVE;
}
#endif

//-----------------------------------------------------------------------------
void
VideoReceiver::_updateTimer()
{
#if defined(QGC_GST_STREAMING)
    if(_stopping || _starting) {
        return;
    }

    if(_streaming) {
        if(!_videoRunning) {
            _videoRunning = true;
            emit videoRunningChanged();
        }
    } else {
        if(_videoRunning) {
            _videoRunning = false;
            emit videoRunningChanged();
        }
    }

    if(_videoRunning) {
        uint32_t timeout = 2;

        const qint64 now = QDateTime::currentSecsSinceEpoch();
        if(now - _lastFrameTime > timeout) {
            stop();
            _stop = false;
        }
    } else {
        // FIXME: AV: if pipeline is _running but not _streaming for some time then we need to restart
        if(!_stop && !_running && !_uri.isEmpty() && true) {
            start();
        }
    }
#endif
}

