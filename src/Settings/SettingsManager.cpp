#include "SettingManager.h"
#include <QDir>
#include <QMutex>

SettingManager::SettingManager(){
    log.info("SettingsManager is Creating");

    this->read_write = new QSettings("./conf/setting.ini", QSettings::IniFormat);
    qDebug() << "ini 在" << read_write->fileName();
    this->InitSettings();
    //此时应该已经将所有的成员都初始化了

    QString localPath = QCoreApplication::applicationDirPath();

    this->videoSavePath = localPath + "/resource/videos";
    this->grapImageSavePath = localPath + "/resource/images";

    QDir dir;
    if( !dir.exists(this->videoSavePath) ){
        dir.mkpath(this->videoSavePath);
    }
    if( !dir.exists(this->grapImageSavePath)){
        dir.mkpath(this->grapImageSavePath);
    }


    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    qmlRegisterUncreatableType<SettingManager>("Rov.SettingsManager", 1, 0, "SettingsManager", "Reference only");


}

SettingManager::~SettingManager()
{
    delete read_write;

}

///
/// \brief SettingManager::InitSettings 从ini文件中获取并初始化
///
void SettingManager::InitSettings()
{
    log.info("InitSettings!");
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
        tmp = QString( "0" );
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
        tmp = QString( "0" );
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
}

QString SettingManager::getImagePath()
{
    QString savePath = this->grapImageSavePath;
    QString imageFile = savePath + "/"
            + QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss")
            + ".png";
    return imageFile;
}

void SettingManager::run(){
    //server
    connect(this, &SettingManager::serverUriChanged, this, [=](){
        read_write->setValue("server/ip", this->uri);
        log.info("server ip changed to " + this->uri);
    });
    connect(this, &SettingManager::serverPortChanged, this, [=](){
        read_write->setValue("server/port", this->port);
        log.info("server port changed to "+ this->port);
    });
    //video
    connect(this, &SettingManager::videoTypeChanged, this, [=](){
        read_write->setValue("video/type", this->stream_type);
        log.info("video type changed to " + QString(this->stream_type) + " ");
    });
    connect(this, &SettingManager::videoUriChanged, this, [=](){
        read_write->setValue("video/uri", this->video_uri);
        log.info("video url changed to " + this->video_uri);
    });
    connect(this, &SettingManager::videoPortChanged, this, [=](){
        read_write->setValue("video/port", this->video_port);
        log.info("video port changed to " + this->video_port);
    });
    //themal video
    connect(this, &SettingManager::thermalVideoTypeChanged, this, [=](){
        read_write->setValue("thermalvideo/type", this->stream_type_2);
        log.info("thermal video type changed to " + QString(this->stream_type_2));
    });
    connect(this, &SettingManager::thermalVideoUriChanged, this, [=](){
        read_write->setValue("thermalvideo/uri", this->thermal_video_uri);
        log.info("thermal video url changed to " + this->thermal_video_uri);
    });
    connect(this, &SettingManager::thermalVideoPortChanged, this, [=](){
        read_write->setValue("thermalvideo/port", this->thermal_video_port);
        log.info("thermal video port changed to " + this->thermal_video_port);
    });
    //enable
    connect(this, &SettingManager::checkoutChanged, this , [=]() {
        read_write->setValue("enable/checkout", this->enableCheck);
        QString tmp = this->enableCheck? "ON" : "OFF";
        log.info("Checkout Enable Switch is " + tmp);
    });

    connect(this, &SettingManager::lowModeChanged, this, [=](){
        read_write->setValue("enable/lowMode", this->lowMode);
        QString tmp = this->lowMode? "ON" : "OFF";
        log.info("LowMode Enable Switch is " + tmp);
    });

    //宽高
    connect(this, &SettingManager::winWidthChanged, this, [=](){
        read_write->setValue("width", this->win_w );
        log.info("height changed to " +QString (this->win_w) );
    });
    connect(this, &SettingManager::winHeightChanged, this, [=](){
        read_write->setValue("height", this->win_h );
        log.info("height changed to " +QString (this->win_h) );
    });
    exec();
}

void SettingManager::udpSettings()
{
//    static QMutex mx;
//    mx.lock();
    log.info("SettingManager::udpSettings ()") ;

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

void SettingManager::setEnableCheckout(const bool enable)
{
    this->enableCheck = enable;

    emit checkoutChanged();
}

void SettingManager::setLowMode(bool mode)
{
    this->lowMode = mode;

    emit lowModeChanged();
}

void SettingManager::setWindowWidth(int width)
{
    this->win_w = width;

    emit winWidthChanged();
}

void SettingManager::setWindowHeight(int height)
{
    this->win_h = height;

    emit winHeightChanged();
}

void SettingManager::setServerUri(QString u)
{
    this->uri = u;

    emit serverUriChanged();
}

void SettingManager::setServerPort(QString p)
{
    this->port = p;

    emit serverPortChanged();
}

void SettingManager::setStreamType(const int t)
{
    this->stream_type = (STREAMING_TYPE) t;

    emit videoTypeChanged();
}

void SettingManager::setStreamType_2(const int t)
{
    this->stream_type_2 = (STREAMING_TYPE) t;

    emit thermalVideoTypeChanged();
}

void SettingManager::setVideoUrl(const QString u)
{
   this->video_uri = u;

    emit videoUriChanged();
}

void SettingManager::setVideoPort(const QString p)
{
    this->video_port = p;

    emit videoPortChanged();
}

void SettingManager::setThermalVideoUrl(const QString u)
{
    this->thermal_video_uri = u;

    emit thermalVideoUriChanged();
}

void SettingManager::setThermalVideoPort(const QString p)
{
    this->thermal_video_port = p;

    emit thermalVideoPortChanged();
}

void SettingManager::setAudioUrl(const QString u)
{
    this->audio_uri = u;
}

void SettingManager::setAudioPort(const QString p)
{
    this->audio_port = p;
}
