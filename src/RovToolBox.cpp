#include "RovToolbox.h"

RovToolbox::RovToolbox(QObject* parent) : QObject(parent)
{
    this->settingsManager = new SettingsManager();
    this->socketManager = new SocketManager();
    this->videoManager = new VideoManager() ;
}
