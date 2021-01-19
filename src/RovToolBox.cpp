#include "RovToolBox.h"

RovToolbox::RovToolbox(QObject* parent) : QObject(parent)
{
    this->rovControl = new RovControlCore();
    this->settingsManager = new SettingsManager();
    this->videoManager = new VideoManager() ;
    this->socketManager = new SocketManager();
    this->keyManager = new KeyManager();
    this->joystickManager = new JoyStickManager();
    this->joystickSettings = new JoyStickSettings;

    this->socketManager->getThread()->start();
    this->settingsManager->start();
//    this->videoManager->start();
//        connect(this->joystickManager,
//                &JoyStickManager::onLeftAxisXChanged,
//                this, [=](int value){
//            qDebug() << value;
//        });
}

RovToolbox::~RovToolbox()
{
    delete joystickSettings;
    delete videoManager;
}


