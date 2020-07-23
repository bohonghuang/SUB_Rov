#include "RovToolBox.h"
#include "RovApplication.h"
#include "SettingManager.h"
#include "JoyManager.h"
#include "VideoManager.h"
#include "KeyManager.h"
#include "SocketManager.h"
#include "RovControlCore.h"
#include <QDebug>

RovToolBox::RovToolBox(RovApplication* app)
{
    qDebug() << "RovToolBox::RovToolBox()";
    this->settingManager = new SettingManager();
    this->socketManager = new SocketManager();
    this->joyManager = new JoyManager();
    this->videoManager = new VideoManager();
    this->keyManager = new KeyManager();
    this->controler = new RovControlCore();

    qDebug() << "Now Create Toolbox Complete";
}
RovToolBox::RovToolBox(){
    qDebug() << "RovToolBox::RovToolBox()";

    this->settingManager = new SettingManager();
    this->socketManager = new SocketManager();
    this->joyManager = new JoyManager();
    this->videoManager = new VideoManager();
    this->keyManager = new KeyManager();




    qDebug("Children were created");
//    if(this->videoManager!=nullptr)
//        this->getVideoManager()->setUri("udp://0.0.0.0:5600");
    qDebug() << "Now Create Toolbox Complete";

}
void RovToolBox::setInit()
{
    qDebug() << "RovToolBox::setInit()";
//    socketManager->start();

    socketManager->updateSettings();
    videoManager->initManager();
    //在 updateSettings 做了init；
    qDebug("End init");

}

SocketManager* RovToolBox::getSocketManager()
{
    qDebug() << "Now in getSocketManager()";
    return this->socketManager;
}

SettingManager * RovToolBox::getSettingManager()
{
    return this->settingManager;
}
