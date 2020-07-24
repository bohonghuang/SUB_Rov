#include "RovApplication.h"
#include <QNetworkProxyFactory>
#include <QtBluetooth/QBluetoothLocalDevice>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QSettings>
#include <QDir>
#include <QRunnable>
#include <QtQml>
#include <QQuickWindow>

#include "SettingManager.h"
#include "VideoManager.h"
#include "VideoStreaming.h"
#include "SocketManager.h"
#include <KeyManager.h>

RovApplication* RovApplication::_app = nullptr;

class FinishVideoManager : public QRunnable
{
private:
    VideoManager* manager;
public:
    FinishVideoManager(VideoManager* v) : manager(v)
    {
    }
    void run(){
        qDebug("FinishVideoManager::run().") ;
        manager->initVideo();
    }
};


RovApplication::RovApplication(int& argc, char*argv[])
    : QApplication          (argc, argv)
{
    QCoreApplication::setOrganizationName("Rocael");
    QCoreApplication::setOrganizationDomain("Rocael.xyz");
    QCoreApplication::setApplicationName("Rov");
    QCoreApplication::setApplicationVersion("1.0");

    qDebug() << "RovApplication::RovApplication()";
    _app = this;
    msecsElapsedTime.start();
    // Setup for network proxy support
    QNetworkProxyFactory::setUseSystemConfiguration(true);


    // Initialize Bluetooth
    //#ifdef QGC_ENABLE_BLUETOOTH
#ifdef ROV_ENABLE_BLUETOOTH
    QBluetoothLocalDevice localDevice;
    if (localDevice.isValid())
    {
        bluetoothAvailable = true;
    }
#endif

    int gstDebugLevel = 1;
    // Initialize Video Streaming
    initializeVideoStreaming(argc, argv, gstDebugLevel);

    this->toolbox = new RovToolBox(this);
    this->toolbox->setInit();
    qDebug() << toolbox;
    qDebug("End it");
}

void RovApplication::setLanguage(){

}

void RovApplication::shutdown(){
    delete qmlAppEngine;

    delete toolbox;
}
bool RovApplication::initAppBoot()
{
    qDebug("RovApplication::initAppBoot()");
    QQmlApplicationEngine* pEngine = new QQmlApplicationEngine(this);
    pEngine->addImportPath("qrc:/");
    pEngine->rootContext()->setContextProperty("socketManager", toolbox->getSocketManager());
    pEngine->rootContext()->setContextProperty("sendManager", toolbox->getSocketManager()->getSendManager());
    pEngine->rootContext()->setContextProperty("videoManager", toolbox->getVideoManager());
    pEngine->rootContext()->setContextProperty("receiveManager", toolbox->getSocketManager()->getReceiveManager());
    pEngine->rootContext()->setContextProperty("rovControl", toolbox->getRovControlCore() );
    pEngine->rootContext()->setContextProperty("keyManager", toolbox->getKeyManager());
    pEngine->rootContext()->setContextProperty("settingsMaanger", toolbox->getSettingManager());

    qmlRegisterUncreatableType<VideoManager>("Rov.VideoManager",1, 0, "VideoManager", "Reference only");
    qmlRegisterUncreatableType<SocketManager>("Rov.SocketManager",1, 0, "SocketManager", "Reference only");
    qmlRegisterUncreatableType<ReceiveManager>("Rov.ReceiveManager",1, 0, "ReceiveManager", "Reference only");
    qmlRegisterUncreatableType<SendManager>("Rov.SendManager",1, 0, "SendManager", "Reference only");
    qmlRegisterUncreatableType<RovControlCore>("Rov.Controler",1, 0, "RovControlCore", "Reference only");


    pEngine->load(QUrl(QStringLiteral("qrc:/main.qml")));

    qmlAppEngine = pEngine;

    QQuickWindow * rootWindow = (QQuickWindow*)rovApp()->MainRootWindow();

    if(rootWindow){
        qDebug("rootWindow has");
        rootWindow->scheduleRenderJob(new FinishVideoManager(toolbox->getVideoManager()),
                                      QQuickWindow::BeforeSynchronizingStage);
    }

//    QTimer timer;
//    timer.interval();

    return true;
}
RovApplication::~RovApplication(){
    _app = nullptr;
}
RovApplication * rovApp(void)
{
    return RovApplication::_app;
}
void RovApplication::openVideoSettingWindow()
{

}

QObject* RovApplication::rootQmlObject ()
{
    if(this->qmlAppEngine && this->qmlAppEngine->rootObjects().size())
    {
        return this->qmlAppEngine->rootObjects()[0];
    }
    return nullptr;
}
void RovApplication::initCommon(){
}

void RovApplication::showMessage(const QString&message)
{

}

bool RovApplication::isInternetAvailable(){
        return true;
}

QQuickItem* RovApplication::MainRootWindow()
{
    if(!this->mainRootWindow)
        this->mainRootWindow = reinterpret_cast<QQuickItem*>(rootQmlObject());
    return this->mainRootWindow;
}

bool RovApplication::checkTelemetrySavePath(bool useMessageBox)
{
    QString saveDirPath = "/video/";
        if (saveDirPath.isEmpty()) {
            QString error = tr("Unable to save telemetry log. Application save directory is not set.");
            showMessage(error);
            return false;
        }

        QDir saveDir(saveDirPath);
        if (!saveDir.exists()) {
            QString error = tr("Unable to save telemetry log. Telemetry save directory \"%1\" does not exist.").arg(saveDirPath);
            showMessage(error);
            return false;
        }

        return true;
}


bool RovApplication::pareseVersionText(const QString& versionString,
                                       int & majorVersion,
                                       int & minorVersion,
                                       int & buildVersion)
{
    QRegularExpression regExp("v(\\d+)\\.(\\d+)\\.(\\d+)");
    QRegularExpressionMatch match = regExp.match(versionString);
    if (match.hasMatch() && match.lastCapturedIndex() == 3) {
        majorVersion = match.captured(1).toInt();
        minorVersion = match.captured(2).toInt();
        buildVersion = match.captured(3).toInt();
        return true;
    }

    return false;
}

void RovApplication::checkForNewVersion(){

}
