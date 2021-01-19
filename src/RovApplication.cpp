#include "RovApplication.h"
#include <QQmlApplicationEngine>

#include <QDir>
#include <QQuickItem>

#include "videostreaming/ImageProvider.h"
#include "RovToolBox.h"
#include "Settings/joysticksettings.h"
#include "joystick/joystickmanager.h"
#include <QtQml>


RovApplication* RovApplication::_app = nullptr;

RovApplication::RovApplication(int& argc, char* argv[]) : QGuiApplication(argc, argv)
{
    QGuiApplication::setOrganizationName("Sub");
    QGuiApplication::setOrganizationDomain("jmu.edu.cn");
    QGuiApplication::setApplicationName("SUB_APP");
    QGuiApplication::setApplicationVersion("0.22");
    //
    QNetworkProxyFactory::setUseSystemConfiguration(true);

    qDebug("RovApplication() --> ");
    _app = this;

    checkSavePath();

    this->toolbox = new RovToolbox();

//    myThread = new QThread(this);

    initAppBoot();
    listenJoystick();

}

RovApplication::~RovApplication(){
    this->_app = nullptr;
//    this->getToolbox()->getVideoManager()->stopWork();
    delete toolbox;
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
    engine->rootContext()->setContextProperty("videoManager", toolbox->getVideoManager() );

    engine->addImageProvider(QLatin1String("provider"), toolbox->getVideoManager()->getProvider1());
    engine->addImageProvider(QLatin1String("thermalProvider"), toolbox->getVideoManager()->getProvider2());

    engine->load(QUrl(QStringLiteral("qrc:/main.qml")));

    qDebug() << "Init over";
}

void RovApplication::checkSavePath()
{
    QString local = QGuiApplication::applicationDirPath();
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

}



void RovApplication::listenJoystick()
{
    connect(toolbox->getJoystickManager(), &JoyStickManager::onButtonAChanged, this, [=](bool pressed){
        toolbox->getRovControlCore()->doThings(toolbox->getJoyStickSettings()->getKey(BUTTON_A), pressed);
    } ) ;
    connect(toolbox->getJoystickManager(), &JoyStickManager::onButtonBChanged, this, [=](bool pressed){
        toolbox->getRovControlCore()->doThings(toolbox->getJoyStickSettings()->getKey(BUTTON_B), pressed);
    } ) ;
    connect(toolbox->getJoystickManager(), &JoyStickManager::onButtonXChanged, this, [=](bool pressed){
        toolbox->getRovControlCore()->doThings(toolbox->getJoyStickSettings()->getKey(BUTTON_X), pressed);
    } ) ;
    connect(toolbox->getJoystickManager(), &JoyStickManager::onButtonYChanged, this, [=](bool pressed){
        toolbox->getRovControlCore()->doThings(toolbox->getJoyStickSettings()->getKey(BUTTON_Y), pressed);
    } ) ;
    connect(toolbox->getJoystickManager(), &JoyStickManager::onButtonUpChanged, this, [=](bool pressed){
        toolbox->getRovControlCore()->doThings(toolbox->getJoyStickSettings()->getKey(BUTTON_UP), pressed);
    } ) ;
    connect(toolbox->getJoystickManager(), &JoyStickManager::onButtonRightChanged, this, [=](bool pressed){
        toolbox->getRovControlCore()->doThings(toolbox->getJoyStickSettings()->getKey(BUTTON_RIGHT), pressed);
    } ) ;
    connect(toolbox->getJoystickManager(), &JoyStickManager::onButtonDownChanged, this, [=](bool pressed){
        toolbox->getRovControlCore()->doThings(toolbox->getJoyStickSettings()->getKey(BUTTON_DOWN), pressed);
    } ) ;
    connect(toolbox->getJoystickManager(), &JoyStickManager::onButtonLeftChanged, this, [=](bool pressed){
        toolbox->getRovControlCore()->doThings(toolbox->getJoyStickSettings()->getKey(BUTTON_LEFT), pressed);
    } ) ;
    connect(toolbox->getJoystickManager(), &JoyStickManager::onButtonLBChanged, this, [=](bool pressed){
        toolbox->getRovControlCore()->doThings(toolbox->getJoyStickSettings()->getKey(BUTTON_LB), pressed);
    } ) ;
    connect(toolbox->getJoystickManager(), &JoyStickManager::onButtonRBChanged, this, [=](bool pressed){
        toolbox->getRovControlCore()->doThings(toolbox->getJoyStickSettings()->getKey(BUTTON_RB), pressed);
    } ) ;
    connect(toolbox->getJoystickManager(), &JoyStickManager::onButtonLPChanged, this, [=](bool pressed){
//        toolbox->getRovControlCore()->doThings(toolbox->getJoyStickSettings()->getKey(BUTTON_LP), pressed);
    } ) ;
    connect(toolbox->getJoystickManager(), &JoyStickManager::onButtonRPChanged, this, [=](bool pressed){
//        toolbox->getRovControlCore()->doThings(toolbox->getJoyStickSettings()->getKey(BUTTON_RP), pressed);
    } ) ;
    connect(toolbox->getJoystickManager(), &JoyStickManager::onLeftAxisXChanged, this, [=](int value){
        toolbox->getRovControlCore()->leftRight(value);
    } ) ;
    connect(toolbox->getJoystickManager(), &JoyStickManager::onLeftAxisYChanged, this, [=](int value){
        toolbox->getRovControlCore()->forwardBack(value);
    } ) ;
    connect(toolbox->getJoystickManager(), &JoyStickManager::onRightAxisXChanged, this, [=](int value){
        toolbox->getRovControlCore()->spin(value);
    } ) ;
    connect(toolbox->getJoystickManager(), &JoyStickManager::onRightAxisYChanged, this, [=](int value){
        toolbox->getRovControlCore()->updown(value);
    } ) ;
    connect(toolbox->getJoystickManager(), &JoyStickManager::onLTRTChanged, this, [=](int value){
        if(value > 200)
            toolbox->getRovControlCore()->openManipulator();
        else if (value < 50)
            toolbox->getRovControlCore()->closeManipulator();
        else
            toolbox->getRovControlCore()->normalManipulator();
    } ) ;

    connect(toolbox->getJoystickManager(), &JoyStickManager::onButtonStartChanged, this, [=](bool pressed){
        toolbox->getRovControlCore()->doThings(toolbox->getJoyStickSettings()->getKey(BUTTON_START), pressed);
    } ) ;
    connect(toolbox->getJoystickManager(), &JoyStickManager::onButtonBackChanged, this, [=](bool pressed){
        toolbox->getRovControlCore()->doThings(toolbox->getJoyStickSettings()->getKey(BUTTON_BACK), pressed);
    } ) ;
}


RovApplication* rovApp()
{
    return RovApplication::_app;
}

