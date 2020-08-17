#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include <QThread>

#include <MyLogging.h>
//#include <QImage>

#include <ImageProvider.h>
#include "ImageProvider2.h"

class VideoLogging;
class VideoManager : public QThread
{
    Q_OBJECT
public:
    explicit VideoManager(QObject *parent = nullptr);
    ~VideoManager();
    void startCap1UDP(QString port);
    void startCap2UDP(QString port);
    void startCap1TCP(QString url);
    void startCap2TCP(QString url);
    void stopCap1();
    void stopCap2();
    void startWriter1();
    void startWriter2();
    void stopWriter1();
    void stopWriter2();
    void startThread() ;

    void run() override;

    ImageProvider* getProvider1(){return &this->provider1; }
    ImageProvider2* getProvider2(){return &this->provider2; }
    void work();
    void stopWork();
    cv::Mat strongFrame(cv::Mat mat );
    QImage mat2QImage(const cv::Mat &mat);


public slots:
    void grabImage();
    void restartVideo();
//    bool isRecording() {return this->recording;}
    void startRecord();
    void stopRecord();
    bool isRecording() {return enableWriter1 || enableWriter2;}
private:

private:
    bool enable;
    bool enableCap1;
    bool enableCap2;
    bool enableWriter1;
    bool enableWriter2;

    QThread* myThread;

    cv::VideoCapture capture1;
    cv::VideoCapture capture2;
    cv::VideoWriter writer1;
    cv::VideoWriter writer2;

    cv::Mat frame1;
    cv::Mat frame2;

    ImageProvider provider1;
    ImageProvider2 provider2;

    VideoLogging* log;

signals:
    void workChanged(cv::Mat mat);
    void work2Changed(cv::Mat mat);
    void noframeChanged();
    void frame1Changed();
    void frame2Changed();
    void writer1Changed();
    void writer2Changed();
};
class VideoLogging : public MyLogging
{
public:
    void info(const QString& msg ){ log(msg, INFO, VIDEO_LOGGING); }
    void debug(const QString& msg ){ log(msg, DEBUG, VIDEO_LOGGING); }
    void warning(const QString& msg ){ log(msg, WARNING, VIDEO_LOGGING); }
};
#endif // VIDEOMANAGER_H
