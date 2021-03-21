#include "VideoReceiver.h"

#include "../Settings/SettingsManager.h"
#include <QImage>

VideoReceiver::VideoReceiver(QObject *parent) : QThread(parent)
{
    initReceiver();
}

void VideoReceiver::initReceiver()
{
    this->opened = false;
    this->record = false;
    this->provider = new ImageProvider();
}

void VideoReceiver::setTypeStream(VideoReceiver::TypeStream ts)
{
    this->type = ts;

    emit streamTypeChanged();
}

void VideoReceiver::setUrl(const QString &url)
{
    this->url = url;

    emit urlChanged();
}

void VideoReceiver::setPort(const QString &port)
{
    this->port = port;

    emit portChanged();
}

void VideoReceiver::setOpened(bool open)
{
    this->opened = open;

    emit openedChanged();
}

void VideoReceiver::setRecorded(bool record)
{
    this->record = record;

    emit recordChanged();
}

void VideoReceiver::startVideo()
{
    // 构建启动语句，主要是针对于gstreamer的语句，对于tcp/mjpg的格式的启动方式暂时未知
    // 初步猜测是直接使用地址
    std::string command = "udpsrc port= " + port.toStdString()  +
                              "caps=\"application/x-rtp, "
                              "media=(string)video, encoding-name=(string)H264\" "
                              "! rtph264depay ! h264parse ! avdec_h264 "
                              "! videoconvert ! appsink";
    switch (this->type) {
    case GSTREAMER_UDP_264:
        capture.open( command , cv::CAP_GSTREAMER);
        break;
    case GSTREAMER_UDP_265:
        capture.open( command, cv::CAP_GSTREAMER);
        break;
    case MPEG_TCP:
        capture.open(url.toStdString(), cv::CAP_FFMPEG);
        break;
    }


    if(! capture.isOpened() )
    {
        setOpened(false);
        log.warning("videoCapture open failed!!");
        qDebug() << "Error to open!";
    }
    else{
        setOpened(true);
        log.warning("videoCapture open successed!!");
    }

}

void VideoReceiver::stopVideo()
{
    if(capture.isOpened()){
        capture.release();
        setOpened(false);
    }
}

void VideoReceiver::startRecording()
{
    QString filePath = rovApp()->getToolbox()->getSettingsManager()->getVideoPath();
    QString filename = filePath + "/"
            + QDateTime::currentDateTime().toString("yyyy-MM-dd_hh_mm_ss")
            + ".mp4";
    writer.open(filename.toStdString(), VideoWriter::fourcc('D','I','V','X'), 25.0, cv::Size(1920, 1080), true);

    if( !writer.isOpened()){
        qDebug() << "Record open failed";
        log.warning("VideoWriter open failed");
        setRecorded(false);
    }
    else{
        log.info("VideoWriter open success");
        setRecorded(true);
    }
}

void VideoReceiver::stopRecording()
{
    if( writer.isOpened() ){
        writer.release();
        setRecorded(false);
    }
}

void VideoReceiver::run()
{
    while(1){
        if( capture.isOpened()){
            capture >> frame;
        }

        if(!frame.empty()){
            frame = matStyle(frame);
            provider->img = mat2QImage(frame);

            emit imgChanged();

            if( writer.isOpened() ){
                writer << frame;
            }
        }
        if(waitKey(5) >= 0){
            stopVideo();
            if(writer.isOpened()){
                stopRecording();
            }
            break;
        }
    }
}

Mat VideoReceiver::matStyle(Mat& frame)
{
    return frame;
}

void VideoReceiver::grabImage()
{
    QString filename = rovApp()->getToolbox()->getSettingsManager()->getImagePath();
    if( !frame.empty())
        imwrite(filename.toStdString(), frame);
}

Mat VideoReceiver::qImage2Mat(QImage &img)
{
    Mat mat;
    switch (img.format()) {
    case QImage::Format_RGB888:
        mat = Mat(img.height(), img.width(), CV_8UC3, (void*)img.constBits(), img.bytesPerLine());
        break;
    case QImage::Format_ARGB32_Premultiplied:
        mat = Mat(img.height(), img.width(), CV_8UC4, (void*)img.constBits(), img.bytesPerLine());
        break;

    }

    return mat;
}

QImage VideoReceiver::mat2QImage(Mat &mat)
{

    cvtColor(mat, mat, COLOR_BGR2RGB);
    QImage img((const uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
    return img;

}
