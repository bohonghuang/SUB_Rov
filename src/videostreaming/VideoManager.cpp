#include "VideoManager.h"
#include <QDebug>
#include <QDateTime>
#include <VideoReceiver.h>
#include "RovApplication.h"
#include "SettingManager.h"

typedef enum VIDEO_STREAM_TYPE
{
   VIDEO_STREAM_TYPE_RTSP=0, /* Stream is RTSP | */
   VIDEO_STREAM_TYPE_RTPUDP=1, /* Stream is RTP UDP (URI gives the port number) | */
   VIDEO_STREAM_TYPE_TCP_MPEG=2, /* Stream is MPEG on TCP | */
   VIDEO_STREAM_TYPE_MPEG_TS_H264=3, /* Stream is h.264 on MPEG TS (URI gives the port number) | */
   VIDEO_STREAM_TYPE_ENUM_END=4, /*  | */
} VIDEO_STREAM_TYPE;

typedef enum FILE_FORMAT{
    FILE_FORMAT_MIN,
    FILE_FORMAT_MKV,
    FILE_FORMAT_MOV,
    FILE_FORMAT_MP4,
    FILE_FORMAT_MAX
} FILE_FORMAT;

static const char* kFileExtension[FILE_FORMAT_MAX - FILE_FORMAT_MIN] = {
    "mkv",
    "mov",
    "mp4"
};

VideoManager::VideoManager(){
    qDebug() << "VideoManager::VideoManager()";

    this->videoReceiver = new  VideoReceiver(this);
    this->videoReceiver_second = new VideoReceiver(this);

    connect(this->videoReceiver, &VideoReceiver::recordingChanged, this, [=](){
        if(this->videoReceiver!=nullptr)
            this->recording = this->videoReceiver->recording();

        emit recordingChanged();
    });

}
VideoManager::~VideoManager(){
    delete videoReceiver;
    videoReceiver = nullptr;
    delete videoReceiver_second;
    videoReceiver_second = nullptr;
}

void VideoManager::initManager(){
    //RovTool::setToolbox(toolbox);
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    qmlRegisterUncreatableType<VideoManager> ("Rov.VideoManager", 1, 0, "VideoManager", "Reference only");
    qmlRegisterUncreatableType<VideoReceiver>("Rov.VideoReceiver", 1, 0, "VideoReceiver","Reference only");

    updateSettings();

}
///
/// \brief VideoManager::StartVideo
/// 启动视频
void VideoManager::startVideo(){
    qDebug("VideoManager::startVideo()");
    if(videoReceiver) videoReceiver->start();
    if(videoReceiver_second) videoReceiver_second->start();
    qDebug("End startVideo()");
}

///
/// \brief VideoManager::StopVideo
/// 结束视频
void VideoManager::stopVideo(){
    if(videoReceiver) videoReceiver->stop();
    if(videoReceiver_second) videoReceiver_second->stop();
}

void VideoManager::startRecording()
{
    qDebug() << "VideoManager::startRecording()";
    if( !videoReceiver ){
        qDebug() << tr("Video receiver is not ready.");
        return ;
    }
    if(videoReceiver)
        videoReceiver->startRecording();
    else{
        qDebug() << "videoReceiver is null";
    }
    if(videoReceiver_second) videoReceiver_second->startRecording();


}

void VideoManager::stopRecording()
{
    if(videoReceiver) videoReceiver->stopRecording();
    if(videoReceiver_second) videoReceiver_second->stopRecording();
}

#if defined(QGC_GST_STREAMING)
GstElement*
VideoManager::_makeVideoSink(gpointer widget)
{
    GstElement* sink;

    if ((sink = gst_element_factory_make("qgcvideosinkbin", nullptr)) != nullptr) {
        g_object_set(sink, "widget", widget, NULL);
    } else {
        qCritical() << "VideoManager::_makeVideoSink() failed. Error with gst_element_factory_make('qgcvideosinkbin')";
    }

    return sink;
}
#endif

void VideoManager::initVideo(){
    qDebug("VideoManager::InitVideo().");
#ifdef QGC_GST_STREAMING
    QQuickItem* root = rovApp()->MainRootWindow();
    qDebug("VideoManager::InitVideo()-ifdefined.");
    if (root == nullptr) {
        qDebug("root Mainwindow is null");
        return;
    }

    QQuickItem* widget = root->findChild<QQuickItem*>("videoContent");

    if (widget != nullptr) {
        qDebug("Widget has had");
        videoReceiver->setVideoSink(_makeVideoSink(widget));
    } else {
        qDebug("widget is null");
    }

    widget = root->findChild<QQuickItem*>("thermalVideo");

    if (widget != nullptr) {
        videoReceiver_second->setVideoSink(_makeVideoSink(widget));
    } else {
        qDebug() << "VideoManager::_makeVideoSink() failed. 'thermalVideo' widget not found";
    }
#endif
    qDebug("End of Init().");
}

bool VideoManager::updateSettings(){
    qDebug("VideoManager::updateSettings");
    if(!videoReceiver && !videoReceiver_second)
        return false;

    int type = rovApp()->getToolbox()->getSettingManager()->getStreamType();
    int type2 = rovApp()->getToolbox()->getSettingManager()->getStreamType_2();

    if( videoReceiver ){
        if(type == SettingManager::TCP){
            videoReceiver->setUri(rovApp()->getToolbox()->getSettingManager()->getVideoUrl());
        }
        else if(type == SettingManager::UDP264){
            videoReceiver->setUri(QStringLiteral("udp://0.0.0.0:%1").arg(rovApp()->getToolbox()->getSettingManager()->getVideoPort()));

        }
        else if(type == SettingManager::UDP265){
            videoReceiver->setUri(QStringLiteral("udp265://0.0.0.0:%1").arg(rovApp()->getToolbox()->getSettingManager()->getVideoPort()));

        }
    }

    if(videoReceiver_second){
        if(type2 == SettingManager::TCP){
            videoReceiver_second->setUri(rovApp()->getToolbox()->getSettingManager()->getThermalVideoUrl());
        }
        else if(type2 == SettingManager::UDP264){
            videoReceiver_second->setUri(QStringLiteral("udp://0.0.0.0:%1").arg(rovApp()->getToolbox()->getSettingManager()->getThermalVideoPort()));

        }
        else if(type2 == SettingManager::UDP265){
            videoReceiver_second->setUri(QStringLiteral("udp265://0.0.0.0:%1").arg(rovApp()->getToolbox()->getSettingManager()->getThermalVideoPort()));

        }
    }

    this->initVideo();
    return true;
}

QString VideoManager::getImageFile(){
    return  this->imageFile;
}


//-----------------------------------------------------------------------------
void
VideoManager::restartVideos()
{
    //qCDebug(VideoManagerLog) << "Restart video streaming";
    stopVideo();
    updateSettings();
    startVideo();
}
//-----------------------------------------------------------------------------
void
VideoManager::udpPortChanged()
{
    restartVideos();
}

//-----------------------------------------------------------------------------
void
VideoManager::rtspUrlChanged()
{
    restartVideos();
}

//-----------------------------------------------------------------------------
void
VideoManager::tcpUrlChanged()
{
    restartVideos();
}

//-----------------------------------------------------------------------------
void
VideoManager::lowLatencyModeChanged()
{
    restartVideos();
}


//-----------------------------------------------------------------------------
#ifndef QGC_DISABLE_UVC
//bool
//VideoManager::uvcEnabled()
//{
//    return QCameraInfo::availableCameras().count() > 0;
//}
#endif
