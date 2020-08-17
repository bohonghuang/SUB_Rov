#include "RovApplication.h"
#include <QQmlApplicationEngine>

#include <QDir>
#include <QQuickItem>

#include <ImageProvider.h>
#include <RovToolbox.h>
#include <QtQml>


RovApplication* RovApplication::_app = nullptr;

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

    myThread = new QThread(this);
//    connect(myThread, &QThread::started, this->toolbox->getVideoManager(), &VideoManager::work);
//    connect(myThread, &QThread::finished, getToolbox()->getVideoManager(), &VideoManager::stopWork);
//    this->toolbox->getVideoManager()->moveToThread(myThread);
//    myThread->start();



    initAppBoot();

}

RovApplication::~RovApplication(){
    this->_app = nullptr;
//    this->getToolbox()->getVideoManager()->stopWork();
    delete toolbox;
}

RovApplication *RovApplication::getThis()
{
    return this;
}

void RovApplication::initAppBoot()
{
    qDebug("---> Init App Boot") ;

    QQmlApplicationEngine* engine = new QQmlApplicationEngine(this);
    engine->addImportPath("qrc:/");

    engine->rootContext()->setContextProperty("rovControl", toolbox->getRovControlCore());
    engine->rootContext()->setContextProperty("socketManager", toolbox->getSocketManager());
    engine->rootContext()->setContextProperty("settingsManager", toolbox->getSettingsManager());
    engine->rootContext()->setContextProperty("keyManager", toolbox->getKeyManager());
    engine->rootContext()->setContextProperty("videoManager", toolbox->getVideoManager());
//    engine->rootContext()->setContextProperty("videoReceiver", toolbox->getVideoManager()->getReceiver());
//    engine->rootContext()->setContextProperty("thermalVideoReceiver", toolbox->getVideoManager()->getThermalReceiver());


    engine->addImageProvider(QLatin1String("provider"), toolbox->getVideoManager()->getProvider1());
    engine->addImageProvider(QLatin1String("thermalProvider"), toolbox->getVideoManager()->getProvider2());

    engine->load(QUrl(QStringLiteral("qrc:/main.qml")));

//    this->getToolbox()->getVideoManager()->startThread();
    qDebug() << "Init over";
}

void RovApplication::checkSavePath()
{
    QString local = QApplication::applicationDirPath();
    QString savePath = local + "/resource/videos";
    QDir saveDir(savePath);
    if( !saveDir.exists() ){
        saveDir.mkpath(savePath);
    }

    savePath = local + "/resource/images";
    saveDir = QDir(savePath);
    if( !saveDir.exists() ){
        saveDir.mkpath(savePath);
    }

//    savePath = "/temp";
//    saveDir = QDir(savePath);
//    if( !saveDir.exists() ){
//        saveDir.mkpath(savePath);
//    }

//    savePath = "/config";
//    saveDir = QDir(savePath);
//    if( !saveDir.exists() ){
//        saveDir.mkpath(savePath);
//    }
}


RovApplication* rovApp()
{
    return RovApplication::_app;
}

