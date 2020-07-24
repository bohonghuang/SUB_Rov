#include "RovToolBox.h"
#include "RovApplication.h"
#include "SettingManager.h"
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
    this->videoManager = new VideoManager();
    this->keyManager = new KeyManager();
    this->controler = new RovControlCore();

    qDebug() << "Now Create Toolbox Complete";
}
RovToolBox::RovToolBox(){
    qDebug() << "RovToolBox::RovToolBox()";

    this->settingManager = new SettingManager();
    this->socketManager = new SocketManager();
    this->videoManager = new VideoManager();
    this->keyManager = new KeyManager();
    this->controler = new RovControlCore();
    qDebug() << "Now Create Toolbox Complete";

}
void RovToolBox::setInit()
{
    socketManager->updateSettings();
    videoManager->initManager();
}

SocketManager* RovToolBox::getSocketManager()
{
    return this->socketManager;
}

SettingManager * RovToolBox::getSettingManager()
{
    return this->settingManager;
}
