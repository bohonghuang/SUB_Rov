#include "RovToolbox.h"

RovToolbox::RovToolbox(QObject* parent) : QObject(parent)
{
    this->rovControl = new RovControlCore();
    this->settingsManager = new SettingsManager();
    this->videoManager = new VideoManager() ;
    this->socketManager = new SocketManager();
    this->keyManager = new KeyManager();
    this->socketManager->getThread()->start();
    this->settingsManager->start();
//    this->videoManager->start();
}

RovToolbox::~RovToolbox()
{
    delete videoManager;
}


