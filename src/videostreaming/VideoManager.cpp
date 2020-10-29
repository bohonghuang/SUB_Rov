#include "VideoManager.h"
#include<QThread>
#include <QMetaType>
#include <RovApplication.h>

#include <QMessageBox>

VideoManager::VideoManager(QObject *parent) : QThread(parent)
{
    this->myThread = new QThread(this);
    this->enable = true;
    this->enableCap1 = false;
    this->enableCap2 = false;
    this->enableWriter1 = false;
    this->enableWriter2 = false;
    this->log = new VideoLogging;

    connect( this, &VideoManager::workChanged, this, [=](cv::Mat mat){
        mat = strongFrame(mat);
        this->provider1.img = mat2QImage(mat);
        emit frame1Changed();
    });
    connect( this, &VideoManager::work2Changed, this, [=](cv::Mat mat){
        mat = strongFrame(mat);
        this->provider2.img = mat2QImage(mat);
        emit frame2Changed();
    });

    QTimer *timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &VideoManager::work);
    timer->start(15);

    qmlRegisterUncreatableType<VideoManager>("Rov.VideoManager", 1, 0, "VideoManager", "Reference only");
    qRegisterMetaType<cv::Mat>("cv::Mat");

}

VideoManager::~VideoManager()
{
    this->enable = false;
}

void VideoManager::startCap1UDP(QString port)
{
    if( !rovApp()->getToolbox()->getSettingsManager()->isEnableMainVideo() )
        return ;
    log->info("startCap1UDP");
    QString cmd = QStringLiteral ("udpsrc port=%1 caps=\"application/x-rtp, media=(string)video, encoding-name=(string)H264\" ! rtph264depay ! h264parse ! avdec_h264 ! videoconvert ! appsink")
            .arg(port);

    try {
        capture1.open( cmd.toStdString(), cv::CAP_GSTREAMER);
    }  catch (QString exp) {
        QMessageBox::warning(nullptr,"OpenError!","Capture Open failed! Please checkout the port and the stream!");

    }

    if( capture1.isOpened() ){
        this->enableCap1 = true;
        log->info("Capture1 success");
    }
    else{
        this->enableCap1 = false;
        log->warning("Capture1 failed");
    }
}

void VideoManager::startCap2UDP(QString port)
{
    if( !rovApp()->getToolbox()->getSettingsManager()->isEnableThermal() )
        return ;
    log->info("startCap2UDP");
    capture2.open("udpsrc port=" + port.toStdString() + " "
                  "caps=\"application/x-rtp, "
                  "media=(string)video, encoding-name=(string)H264\" "
                  "! rtph264depay ! h264parse ! avdec_h264 "
                  "! videoconvert ! appsink", cv::CAP_GSTREAMER);

    if( capture2.isOpened() ){
        this->enableCap2 = true;
        log->info("Capture2 success");
    }
    else{
        this->enableCap2 = false;
        log->warning("Capture2 failed");
    }
}

void VideoManager::startCap1TCP(QString url)
{
    if( !rovApp()->getToolbox()->getSettingsManager()->isEnableMainVideo() )
        return ;
    log->info("startCap1TCP");
    capture1.open(url.toStdString());

    if( capture1.isOpened() ){
        log->info(" captrue 1 isOpened in tcp");
        this->enableCap1 = true;
    }
    else{
        log->warning(" captrue 1 failed in tcp");
        this->enableCap1 = false;
    }
}

void VideoManager::startCap2TCP(QString url)
{
    if( !rovApp()->getToolbox()->getSettingsManager()->isEnableThermal() )
        return ;
    log->info("startCap2TCP");
    capture1.open(url.toStdString());

    if( capture2.isOpened() ){
        log->info(" captrue 2 isOpened in tcp");
        this->enableCap2 = true;
    }
    else{
        log->warning(" captrue 2 failed in tcp");
        this->enableCap2 = false;
    }
}

void VideoManager::stopCap1()
{
    capture1.release();
    log->info("Stop Cap 1!");
}

void VideoManager::stopCap2()
{
    capture2.release();
    log->info("Stop Cap 2!");
}

void VideoManager::startWriter1()
{
    if( enableWriter1 )
        return ;
    log->info("Start writer 1!");
    QString filename = rovApp()->getToolbox()->getSettingsManager()->getVideoPath();
    writer1.open( filename.toStdString(),
                  CV_FOURCC('A','2','6','4'),
                  25,
                  cv::Size(1920, 1080));

    if( writer1.isOpened() ){
        enableWriter1 = true;
        log->info("Writer 1 open success!");

        emit writer1Changed();
    }
    else{
        log->info("Writer 1 open failed!");
        enableWriter1 = false;
        emit writer1Changed();
    }
}

void VideoManager::startWriter2()
{
    if( enableWriter2 )
        return ;
    log->info("Start writer 2!");
    QString filename = rovApp()->getToolbox()->getSettingsManager()->getVideoPath();
    writer1.open( filename.toStdString(), CV_FOURCC('D','I','V','X'), 30, cv::Size(1920, 1080));

    if( writer2.isOpened() ){
        enableWriter2 = true;
        log->info("Writer 2 open success!");

        emit writer2Changed();
    }
    else{
        enableWriter2 = false;
        log->info("Writer 2 open failed!");
        emit writer2Changed();
    }
}

void VideoManager::stopWriter1()
{
    if( enableWriter1 == false ) return ;
    enableWriter1 = false;
    writer1.release();

    emit writer1Changed();
    log->info("Stop writer 1!");
}

void VideoManager::stopWriter2()
{
    enableWriter2 = false;
    writer2.release();

    emit writer2Changed();
    log->info("Stop writer 2!");
}

void VideoManager::startThread()
{
    this->myThread->start();
}

void VideoManager::run()
{
    work();
    exec();
}

void VideoManager::grabImage()
{
    if( !frame1.empty() && enableCap1 )
        cv::imwrite( rovApp()->getToolbox()->getSettingsManager()->getImagePath().toStdString()
                     , frame1);
    if( !frame2.empty() && enableCap2 )
        cv::imwrite( rovApp()->getToolbox()->getSettingsManager()->getImagePath().toStdString()
                     , frame2);


    log->info("Grab Image!");
}

void VideoManager::restartVideo()
{
    log->info("Restart Video");

    stopCap1();
    stopCap2();
    bool enable1 = rovApp()->getToolbox()->getSettingsManager()->isEnableMainVideo();
    bool enable2 = rovApp()->getToolbox()->getSettingsManager()->isEnableThermal();
    QString port1 = rovApp()->getToolbox()->getSettingsManager()->getVideoPort() ;
    QString port2 = rovApp()->getToolbox()->getSettingsManager()->getThermalVideoPort() ;

    if( enable1 && enable2 && port1.contains(port2) ){
        rovApp()->getToolbox()->getSettingsManager()->setEnableThermal(false);
    }
    startCap1UDP( port1);
    startCap2UDP(  port2);
}

void VideoManager::startRecord()
{
    log->info("Start Record");
    if( enableCap1 )
        startWriter1();
    else
        stopWriter1();

//    if( enableCap2 )
//        startWriter2();
//    else
//        stopWriter2();
}

void VideoManager::stopRecord()
{
    log->info("Stop Record");
    qDebug() << enableCap1 << " - " << enableWriter1;
    if( enableCap1 && enableWriter1)
        stopWriter1();
//    if( enableCap2 && enableWriter2)
//        stopWriter2();
}

cv::Mat VideoManager::strongFrame(cv::Mat mat)
{
    return mat;
}

void VideoManager::work()
{
        if( enableCap1 ){
            capture1 >> frame1 ;

            emit workChanged(frame1);
            if( enableWriter1)
                writer1 << frame1;
        }
        if( enableCap2 ){
            capture2 >> frame2 ;

            emit work2Changed(frame2);
            if( enableWriter2 )
                writer2 << frame2;
        }

        if( cv::waitKey(5) >= 0){
            emit noframeChanged();
//            break;
        }

}

void VideoManager::stopWork()
{
    log->info("Stop work");
    this->enable = false;
}

QImage VideoManager::mat2QImage(const cv::Mat &mat)
{
//    qDebug() << mat.channels();
    cv::cvtColor(mat,mat,CV_BGR2RGB);
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
