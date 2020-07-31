#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include <QObject>
#include <QSettings>
#include <QLoggingCategory>
#include <QSize>

#include "gst/gst.h"

class JoyManager;
class VideoReceiver;
class RovApplication;

class VideoManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(VideoReceiver*   videoReceiver   READ    getVideoReceiver                           CONSTANT)
    Q_PROPERTY(VideoReceiver*   videoReceiver_second   READ    getVideoReceiver_second             CONSTANT)
    Q_PROPERTY(QString          imageFile       READ    getImageFile                               NOTIFY  imageFileChanged)
    Q_PROPERTY(bool recording READ isRecording NOTIFY recordingChanged)

public:
    VideoManager();
    ~VideoManager();
    void initManager();

    VideoReceiver*  getVideoReceiver()       {return this->videoReceiver;}
    VideoReceiver*  getVideoReceiver_second(){return this->videoReceiver_second;}
    QString         getImageFile();


public slots:
    void restartVideos();
    void startVideo();
    void stopVideo();
    void startRecording();
    void stopRecording();
    bool updateSettings();
    bool isRecording(){return this->recording;}

public:
#if defined(QGC_GST_STREAMING)
    static gboolean _videoSinkQuery (GstPad* pad, GstObject* parent, GstQuery* query);
    GstElement*     _makeVideoSink  (gpointer widget);
#endif

    // 截图
protected slots:
    void udpPortChanged();
    void rtspUrlChanged();
    void tcpUrlChanged();
    void lowLatencyModeChanged();

protected:
    friend class FinishVideoManager;
    void initVideo();

public:
    QString videoFile;
    QString imageFile;

    VideoReceiver* videoReceiver = nullptr;
    VideoReceiver* videoReceiver_second = nullptr;
    bool streaming;
    bool recording;

signals:
    void imageFileChanged();
    void streamingChanged();
    void recordingChanged();
    void videoSizeChanged();

public:


};

#endif // VIDEOMANAGER_H
