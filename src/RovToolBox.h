#ifndef ROVTOOLBOX_H
#define ROVTOOLBOX_H

#include <QObject>
#include "Settings/SettingsManager.h"
#include "Socket/SocketManager.h"
#include "VideoStreaming/VideoManager.h"

class RovToolbox : public QObject
{
    Q_OBJECT
public:
    RovToolbox(QObject* parent = nullptr);
private:
    SettingsManager* settingsManager;
    SocketManager* socketManager;
    VideoManager* videoManager;

public slots:
    SettingsManager* getSettingsManager(){return this->settingsManager; };
    SocketManager* getSocketManager() {return this->socketManager;}
    VideoManager* getVideoManager() {return this->videoManager;}
};

#endif // ROVTOOLBOX_H
