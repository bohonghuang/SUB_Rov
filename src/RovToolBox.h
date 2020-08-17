#ifndef ROVTOOLBOX_H
#define ROVTOOLBOX_H

#include <QObject>
#include "Settings/SettingsManager.h"
#include "Socket/SocketManager.h"
#include "VideoStreaming/VideoManager.h"
#include "RovControlCore.h"
#include <KeyManager.h>

class RovToolbox : public QObject
{
    Q_OBJECT
public:
    RovToolbox(QObject* parent = nullptr);
    ~RovToolbox();
private:
    SettingsManager* settingsManager;
    SocketManager* socketManager;
    VideoManager* videoManager;
    RovControlCore* rovControl;
    KeyManager* keyManager;

public slots:
    SettingsManager* getSettingsManager(){return this->settingsManager; };
    SocketManager* getSocketManager() {return this->socketManager;}
    VideoManager* getVideoManager() {return this->videoManager;}
    RovControlCore* getRovControlCore(){return this->rovControl;}
    KeyManager* getKeyManager(){return this->keyManager;}
};

#endif // ROVTOOLBOX_H
