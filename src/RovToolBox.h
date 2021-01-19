#ifndef ROVTOOLBOX_H
#define ROVTOOLBOX_H

#include <QObject>
#include "Settings/SettingsManager.h"
#include "socket/SocketManager.h"
#include "videostreaming/VideoManager.h"
#include "RovControlCore.h"
#include "keyboard/KeyManager.h"
#include "joystick/joystickmanager.h"
#include "Settings/joysticksettings.h"

class RovToolbox : public QObject
{
    Q_OBJECT
public:
    RovToolbox(QObject* parent = nullptr);
    ~RovToolbox();
private:
    RovControlCore* rovControl;
    SettingsManager* settingsManager;
    SocketManager* socketManager;
    VideoManager* videoManager;
    KeyManager* keyManager;
    JoyStickManager* joystickManager;
    JoyStickSettings* joystickSettings;

public slots:
    SettingsManager* getSettingsManager(){return this->settingsManager; };
    SocketManager* getSocketManager() {return this->socketManager;}
    VideoManager* getVideoManager() {return this->videoManager;}
    RovControlCore* getRovControlCore(){return this->rovControl;}
    KeyManager* getKeyManager(){return this->keyManager;}
    JoyStickManager* getJoystickManager() { return this->joystickManager; }
    JoyStickSettings* getJoyStickSettings() {return this->joystickSettings; }
};

#endif // ROVTOOLBOX_H
