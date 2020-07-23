#ifndef JOYMANAGER_H
#define JOYMANAGER_H

#include <QObject>
#include "SocketManager.h"
#include "RovApplication.h"
#include "RovToolBox.h"
#include "RovBase.h"
#include <RovControlCore.h>
#include <QJoysticks.h>

class JoyManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ isConnected WRITE setConnected NOTIFY connectedChanged)
public:
    explicit JoyManager(QObject* parent = nullptr);
    JoyManager(RovApplication* app, RovToolBox* tool);
    ~JoyManager();

signals:
    void connectedChanged();

public slots:
    void onInformationChanged();
public:
    typedef enum {
        Btn_A, Btn_B, Btn_X, Btn_Y,
        Btn_UP, Btn_Down, Btn_Left, Btn_Right,
        Btn_RB, Btn_RT, Btn_LB, Btn_LT,
        Btn_Start, Btn_Main, Btn_Center
    } JOY_BUTTON;

public:
    Q_INVOKABLE bool isConnected()          {   return this->connected;}
    Q_INVOKABLE void setConnected(bool c)   {   this->connected = c;}

    Q_INVOKABLE void handle_joystick_aciton_axis( int index, double value);
    Q_INVOKABLE void handle_joystick_aciton_button( int index, bool value);
    Q_INVOKABLE void handle_joystick_aciton_povs( int value);

    void doCamera (int index, double value);

    void Axis_Act(int index, double value);
    void Povs_Act( int value);
    void Button_Act(int index);

    void init();
    QJoysticks* getJoysticks(){return this->instance;}
private:
    bool connected;

    void send();

    QJoysticks* instance;
};

#endif // JOYMANAGER_H
