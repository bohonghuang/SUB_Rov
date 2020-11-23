#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include <QThread>
#include <QObject>
#include <imageprovider.h>

//#include <opencv2/core.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>

class VideoManager : public QThread
{
    Q_OBJECT
public:
    VideoManager();
    ~VideoManager();
    void run() override;


    QImage mat2QImage(const cv::Mat &mat);

    ImageProvider* provider;

    cv::VideoCapture capture;
    cv::VideoWriter writer;
    cv::Mat frame;

public slots:
    void startvideo();
    void stopvideo();

signals:
    void onFrameChanged();
};

#endif // VIDEOMANAGER_H
