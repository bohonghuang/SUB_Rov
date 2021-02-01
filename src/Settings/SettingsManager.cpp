#include "SettingsManager.h"
#include <QDebug>

#include "../RovApplication.h"

SettingsManager::SettingsManager(){
    //SettingsLog.info("SettingsManager is Creating");

    this->log = new SettingsLoggging;
    QString local = QCoreApplication::applicationDirPath();

    // 保存配置文件于用户目录下
    QString iniPath = QDir::homePath()+"/.sub/conf";
    QDir dir(iniPath);
    if( !dir.exists() ) {
        dir.mkpath(iniPath);
    }
    qDebug() << iniPath;
    this->read_write = new QSettings(iniPath+"/setting.ini", QSettings::IniFormat);
//    qDebug() << "ini in" << read_write->fileName();
    

//    QString localPath = QCoreApplication::applicationDirPath();
    QDir localPath(local);
    localPath.cdUp();
    this->videoSavePath = localPath.path() + "/resource/videos";
    this->grapImageSavePath = localPath.path() + "/resource/images";
    qDebug() << this->videoSavePath;
    this->enableMainVideo = true;
    this->enableThermal = false;

    this->thermal_w = 480;
    this->InitSettings();

    qmlRegisterUncreatableType<SettingsManager>("Rov.SettingsManager", 1, 0, "SettingsManager", "Reference only");


}

SettingsManager::~SettingsManager()
{
    delete read_write;

}

///
/// \brief SettingManager::InitSettings 从ini文件中获取并初始化
///
void SettingsManager::InitSettings()
{
    log->info("InitSettings!");
    // server 组
    read_write->beginGroup("server");
    QString tmp = read_write->value("ip").toString();
    if( tmp.isEmpty() ){
        tmp = QString("127.0.0.1");
        read_write->setValue("ip", tmp );
    }
    this->uri = tmp;
    tmp = read_write->value("port").toString();
    if( tmp.isEmpty() ){
        tmp = QString("8888");
        read_write->setValue("port", tmp);
    }
    this->port = tmp;
    read_write->endGroup();


    // video 组
    read_write->beginGroup("video");
    tmp = read_write->value("uri").toString();
    if( tmp.isEmpty() ){
        tmp = QString("127.0.0.1");
        read_write->setValue("uri", tmp );
    }
    this->video_uri = tmp;
    tmp = read_write->value("port").toString();
    if( tmp.isEmpty() ){
        tmp = QString("5600");
        read_write->setValue("port", tmp);
    }
    this->video_port = tmp;
    tmp = read_write->value("type").toString();
    if( tmp.isEmpty() ){
        tmp = QString( "1" );
        read_write->setValue("type", tmp.toInt());
    }
    this->stream_type = (STREAMING_TYPE) tmp.toInt();
    read_write->endGroup();



    // thermal video 组
    read_write->beginGroup("thermalvideo");
    tmp = read_write->value("uri").toString();
    if( tmp.isEmpty() ){
        tmp = QString("127.0.0.1");
        read_write->setValue("uri", tmp );
    }
    this->thermal_video_uri = tmp;
    tmp = read_write->value("port").toString();
    if( tmp.isEmpty() ){
        tmp = QString("5601");
        read_write->setValue("port", tmp);
    }
    this->thermal_video_port = tmp;
    tmp = read_write->value("type").toString();
    if( tmp.isEmpty() ){
        tmp = QString( "1" );
        read_write->setValue("type", tmp.toInt());
    }
    this->stream_type_2 = (STREAMING_TYPE) tmp.toInt();
    read_write->endGroup();



    // audio 组
    read_write->beginGroup("audio");
    tmp = read_write->value("uri").toString();
    if( tmp.isEmpty() ){
        tmp = QString("127.0.0.1");
        read_write->setValue("uri", tmp );
    }
    this->audio_uri = tmp;
    tmp = read_write->value("port").toString();
    if( tmp.isEmpty() ){
        tmp = QString("5601");
        read_write->setValue("port", tmp);
    }
    this->audio_port = tmp;
    read_write->endGroup();



    // mainwindow 组
    read_write->beginGroup("mainwindow");
    tmp = read_write->value("x").toString();
    if( tmp.isEmpty() ){
        tmp = QString("10");
        read_write->setValue("x", tmp.toInt() );
    }
    this->win_x = tmp.toInt() ;
    tmp = read_write->value("y").toString();
    if( tmp.isEmpty() ){
        tmp = QString("10");
        read_write->setValue("y", tmp.toInt() );
    }
    this->win_y = tmp.toInt() ;
    tmp = read_write->value("width").toString();
    if( tmp.isEmpty() ){
        tmp = QString("1600");
        read_write->setValue("width", tmp.toInt() );
    }
    this->win_w = tmp.toInt() ;
    tmp = read_write->value("height").toString();
    if( tmp.isEmpty() ){
        tmp = QString("900");
        read_write->setValue("height", tmp.toInt() );
    }
    this->win_h = tmp.toInt() ;
    read_write->endGroup();


    //enable 组
    read_write->beginGroup("enable");
    tmp = read_write->value("checkout").toString();
    if( tmp.isEmpty() ){
        tmp = QString("true");
        read_write->setValue("checkout", tmp);
    }
    this->enableCheck = tmp.contains("true") ? true : false ;
    tmp = read_write->value("lowMode").toString();
    if( tmp.isEmpty() ){
        tmp = QString("true");
        read_write->setValue("lowMode",tmp);
    }
    this->lowMode = tmp.contains("true")? true: false;
    read_write->endGroup();


    read_write->beginGroup("videoSave");
    tmp = read_write->value("path").toString();
    if( tmp.isEmpty() ){
        tmp = QString(this->videoSavePath);
        read_write->setValue("path", tmp);
    }
    this->videoSavePath = tmp;
    read_write->endGroup();

    read_write->beginGroup("frame");
    tmp = read_write->value("black").toString();
    if( tmp.isEmpty() ){
        tmp = QString(this->enableBlack?"true":"false");
        read_write->setValue("black", tmp);
    }
    this->enableBlack = tmp.contains("true") ? true : false;
    tmp = read_write->value("area").toString();
    if( tmp.isEmpty() ){
        tmp = QString::number(this->frameArea);
        read_write->setValue("path", tmp);
    }
    this->frameArea = tmp.toInt();
    read_write->endGroup();
}

QString SettingsManager::getImagePath()
{
    QString savePath = this->grapImageSavePath;
    QString imageFile = savePath + "/"
            + QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss")
            + ".png";
    return imageFile;
}

void SettingsManager::setVideoSavePath(QString vs)
{
    QString t = vs;

    if( t.startsWith("file")  || t.startsWith("File") ){
        t = t.mid(8); // 删除 'file://'
    }

    this->videoSavePath = t;

    emit onVideoPathChanged();
}

void SettingsManager::run(){
    //server
    connect(this, &SettingsManager::serverUriChanged, this, [=](){
        read_write->setValue("server/ip", this->uri);
        log->info("server ip changed to " + this->uri);
    });
    connect(this, &SettingsManager::serverPortChanged, this, [=](){
        read_write->setValue("server/port", this->port);
        log->info("server port changed to "+ this->port);
    });
    //video
    connect(this, &SettingsManager::videoTypeChanged, this, [=](){
        read_write->setValue("video/type", this->stream_type);
//        log->info("video type changed to " + QString(this->stream_type) + " ");
    });
    connect(this, &SettingsManager::videoUriChanged, this, [=](){
        read_write->setValue("video/uri", this->video_uri);
        log->info("video url changed to " + this->video_uri);
    });
    connect(this, &SettingsManager::videoPortChanged, this, [=](){
        read_write->setValue("video/port", this->video_port);
        log->info("video port changed to " + this->video_port);
    });
    //themal video
    connect(this, &SettingsManager::thermalVideoTypeChanged, this, [=](){
        read_write->setValue("thermalvideo/type", this->stream_type_2);
//        log->info("thermal video type changed to " + QString(this->stream_type_2));
    });
    connect(this, &SettingsManager::thermalVideoUriChanged, this, [=](){
        read_write->setValue("thermalvideo/uri", this->thermal_video_uri);
        log->info("thermal video url changed to " + this->thermal_video_uri);
    });
    connect(this, &SettingsManager::thermalVideoPortChanged, this, [=](){
        read_write->setValue("thermalvideo/port", this->thermal_video_port);
        log->info("thermal video port changed to " + this->thermal_video_port);
    });
    //enable
    connect(this, &SettingsManager::checkoutChanged, this , [=]() {
        read_write->setValue("enable/checkout", this->enableCheck);
        QString tmp = this->enableCheck? "ON" : "OFF";
        log->info("Checkout Enable Switch is " + tmp);
    });

    connect(this, &SettingsManager::lowModeChanged, this, [=](){
        read_write->setValue("enable/lowMode", this->lowMode);
        QString tmp = this->lowMode? "ON" : "OFF";
        log->info("LowMode Enable Switch is " + tmp);
    });

    //宽高
    connect(this, &SettingsManager::winWidthChanged, this, [=](){
        read_write->setValue("width", this->win_w );
//        log->info("height changed to " +QString (this->win_w) );
    });
    connect(this, &SettingsManager::winHeightChanged, this, [=](){
        read_write->setValue("height", this->win_h );
//        log->info("height changed to " +QString (this->win_h) );
    });


    connect(this, &SettingsManager::onVideoPathChanged, this, [=](){
        read_write->setValue("videoSave/path", this->videoSavePath );
//        log->info("height changed to " +QString (this->win_h) );
    });
    connect(this, &SettingsManager::onEnableBlackChanged, this, [=](){
        read_write->setValue("frame/black", this->enableBlack );
//        log->info("height changed to " +QString (this->win_h) );
    });
    connect(this, &SettingsManager::winHeightChanged, this, [=](){
        read_write->setValue("frame/area", this->frameArea );
//        log->info("height changed to " +QString (this->win_h) );
    });
    exec();
}

void SettingsManager::udpSettings()
{
//    static QMutex mx;
//    mx.lock();
    log->info("SettingManager::udpSettings ()") ;

    read_write->setValue("server/ip", this->uri);
    read_write->setValue("server/port", this->port);
    read_write->setValue("video/type", this->stream_type);
    read_write->setValue("video/uri", this->video_uri);
    read_write->setValue("video/port", this->video_port);
    read_write->setValue("thermalvideo/type", this->stream_type_2);
    read_write->setValue("thermalvideo/uri", this->thermal_video_uri);
    read_write->setValue("thermalvideo/port", this->thermal_video_port);
    read_write->setValue("audio/uri", this->audio_uri);
    read_write->setValue("audio/port", this->audio_port);


    //mx.unlock();
}

void SettingsManager::setEnableCheckout(const bool enable)
{
    this->enableCheck = enable;

    emit checkoutChanged();
}

void SettingsManager::setLowMode(bool mode)
{
    this->lowMode = mode;

    emit lowModeChanged();
}

void SettingsManager::setEnableMainVideo(bool enable)
{
    this->enableMainVideo = enable;
    emit enableMainChanged();
}

void SettingsManager::setEnableThermal(bool enable)
{
    this->enableThermal = enable;
    emit enableThermalChanged();
}

void SettingsManager::setWindowWidth(int width)
{
    this->win_w = width;

    emit winWidthChanged();
}

void SettingsManager::setWindowHeight(int height)
{
    this->win_h = height;

    emit winHeightChanged();
}

QString SettingsManager::getVideoPath()
{
    static int count = 1;
    QString savePath = this->videoSavePath;
    QString videoFile = savePath + "/"
            + QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss")
            + ".mp4";
    count ++;
    return videoFile;
}

void SettingsManager::setImagePath(QString is)
{
    QString t = is;

    if( t.startsWith("file")  || t.startsWith("File") ){
        t = t.mid(8); // 删除 'file://'
    }
    this->grapImageSavePath = t;


    emit onImagePathChanged();
}

void SettingsManager::setServerUri(QString u)
{
    this->uri = u;

    emit serverUriChanged();
}

void SettingsManager::setServerPort(QString p)
{
    this->port = p;

    emit serverPortChanged();
}

void SettingsManager::setStreamType(const int t)
{
    this->stream_type = (STREAMING_TYPE) t;

    emit videoTypeChanged();
}

void SettingsManager::setStreamType_2(const int t)
{
    this->stream_type_2 = (STREAMING_TYPE) t;

    emit thermalVideoTypeChanged();
}

void SettingsManager::setVideoUrl(const QString u)
{
   this->video_uri = u;

    emit videoUriChanged();
}

void SettingsManager::setVideoPort(const QString p)
{
    this->video_port = p;

    emit videoPortChanged();
}

void SettingsManager::setThermalVideoUrl(const QString u)
{
    if( this->thermal_video_uri.contains(this->video_uri)){
        log->warning("The thermal url is same of main url");
        return ;
    }
    this->thermal_video_uri = u;

    emit thermalVideoUriChanged();
}

void SettingsManager::setThermalVideoPort(const QString p)
{
    if( this->thermal_video_port.contains(this->video_port)){
        log->warning("The thermal port is same of main port");
        return ;
    }
    this->thermal_video_port = p;

    emit thermalVideoPortChanged();
}

void SettingsManager::setAudioUrl(const QString u)
{
    this->audio_uri = u;
}

void SettingsManager::setAudioPort(const QString p)
{
    this->audio_port = p;
}
