#include "videomanager.h"
//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>

VideoManager::VideoManager() : QThread(parent())
{
//    connect(this, )
    this->provider = new ImageProvider();
}

VideoManager::~VideoManager()
{

    delete this;
//    capture->release();
//    delete capture;
}

void VideoManager::run()
{
    QString cmd = QStringLiteral ("udpsrc port=%1 caps=\"application/x-rtp, media=(string)video, encoding-name=(string)H264\" ! rtph264depay ! h264parse ! avdec_h264 ! videoconvert ! appsink")
                .arg("5600");

//    this->capture = new cv::VideoCapture();
    capture.open(cmd.toStdString(), cv::CAP_GSTREAMER);

    qDebug() << "opened";
    if( capture.isOpened()){
        qDebug() << "open success";
    }
    int flag = 0;
    while(true){
        if( flag == 0 )
        {
            qDebug() << "Run";
            flag = 1;
        }
        capture >> frame;
        this->provider->img = mat2QImage(frame);
        emit onFrameChanged();
    }

    exec();
}

void VideoManager::startvideo()
{
    this->start();

}

void VideoManager::stopvideo()
{

}


QImage VideoManager::mat2QImage(const cv::Mat &mat)
{
//    qDebug() << mat.channels();
//    cv::cvtColor(mat,mat,RGB_MASK);
    switch ( mat.type() ) {
    // 8bits, 4 channel
    case CV_8UC4:{
        QImage image( mat.data, mat.cols, mat.rows, static_cast<int>(mat.step),
                      QImage::Format_ARGB32);
        return image;
    }
    // 8bits, 3 channel
    case CV_8UC3:{
        QImage image( mat.data, mat.cols, mat.rows, static_cast<int>(mat.step),
                      QImage::Format_RGB888);
        return image;
    }
    // 8bits, 1 channel
    case CV_8UC1:{
        QImage image( mat.data, mat.cols, mat.rows, static_cast<int>(mat.step),
                      QImage::Format_Grayscale8);
        return image;
    }
    default:
        qWarning() << "VideoManager::mat2Qimage() - cv::mat image type not handled in switch: " << mat.type() ;
        break;
    }
    return QImage();
}
