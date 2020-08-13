#ifndef VIDEORECEIVER_H
#define VIDEORECEIVER_H

#include <QObject>
#include <QThread>

#include <opencv2/opencv.hpp>
#include "../Log/MyLogging.h"
#include "../RovApplication.h"
#include "ImageProvider.h"

class VideoLogging: public MyLogging
{
public:
    void info(const QString& msg ){ log(msg, INFO, VIDEO_LOGGING); }
    void debug(const QString& msg ){ log(msg, DEBUG, VIDEO_LOGGING); }
    void warning(const QString& msg ){ log(msg, WARNING, VIDEO_LOGGING); }
};

using namespace cv;

class VideoReceiver : public QThread
{
    Q_OBJECT
public:
    explicit VideoReceiver(QObject *parent = nullptr);

    typedef enum {
        GSTREAMER_UDP_264,
        GSTREAMER_UDP_265,
        MPEG_TCP
    } TypeStream;

    //初始化
    void initReceiver();
    // 设置流类型
    void setTypeStream(TypeStream ts);
    // 设置链接地址（在tcp模式下）
    void setUrl(const QString& url);
    // 设置端口，在udp模式下
    void setPort(const QString& port);
    // 获取当前的open状态
    bool isOpened() {return this->opened;   }
    void setOpened(bool open);
    // 录制状态
    bool isRecorded() {return this->record; }
    void setRecorded(bool record);

    ImageProvider* getProvider(){return this->provider;}


    // 开始拉流
    void startVideo();
    // 停止拉流
    void stopVideo();
    // 开始录像
    void startRecording();
    // 停止录像
    void stopRecording();
    // 主循环
    void run() override;
    // 改变帧样式
    Mat matStyle(Mat& frame);
    //截图
    void grabImage();

    //转变
    Mat qImage2Mat(QImage& img);
    QImage mat2QImage(Mat& mat);

private:
    VideoCapture capture;
    VideoWriter writer;
    Mat frame;

    TypeStream type;
    bool record;
    bool opened;

    QString url;
    QString port;

    VideoLogging log;

    int frame_width;
    int frame_height;

    ImageProvider* provider;

signals:
    void streamTypeChanged();
    void urlChanged();
    void portChanged();
    void openedChanged();
    void recordChanged();

    void imgChanged();
};

#endif // VIDEORECEIVER_H
