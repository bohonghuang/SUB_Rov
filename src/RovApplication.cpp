#include "RovApplication.h"
#include <QQmlApplicationEngine>

#include <QDir>

#include "VideoStreaming/ImageProvider.h"

RovApplication::RovApplication(int& argc, char* argv[]) : QApplication(argc, argv)
{
    QApplication::setOrganizationName("Sub");
    QApplication::setOrganizationDomain("jmu.edu.cn");
    QApplication::setApplicationName("SUB_APP");
    QApplication::setApplicationVersion("0.20");
    //
    //QNetworkProxyFactory::setUseSystemConfiguration(true);

    qDebug("RovApplication() --> ");
    _app = this;

    checkSavePath();

    this->toolbox = new RovToolbox();
}

RovApplication::~RovApplication(){
    this->_app = nullptr;
    delete toolbox;
}

void RovApplication::initAppBoot()
{
    qDebug("---> Init App Boot") ;

    QQmlApplicationEngine* engine = new QQmlApplicationEngine(this);
    engine->addImportPath("qrc:/");
    engine->addImageProvider("provider", toolbox->getVideoManager()->getProvider());
    engine->addImageProvider("thermalProvider", toolbox->getVideoManager()->getThermalProvider());


    engine->load(QUrl(QStringLiteral("qrc:/main.qml")));
}

void RovApplication::checkSavePath()
{
    QString savePath = "/resource/videos";
    QDir saveDir(savePath);
    if( !saveDir.exists() ){
        saveDir.mkpath(savePath);
    }

    savePath = "/resource/images";
    saveDir = QDir(savePath);
    if( !saveDir.exists() ){
        saveDir.mkpath(savePath);
    }

    savePath = "/temp";
    saveDir = QDir(savePath);
    if( !saveDir.exists() ){
        saveDir.mkpath(savePath);
    }
}


RovApplication* rovApp(void)
{
    return RovApplication::_app;
}

