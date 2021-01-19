#ifndef JOYSTICKMANAGER_H
#define JOYSTICKMANAGER_H

#include <QObject>
#include "joythread.h"

typedef enum {
    XBOX_360,
    PS2_NORMAL
} TYPE_CONTROLLER;

typedef enum {
    MIN_BTN,
    BUTTON_Y,
    BUTTON_A,
    BUTTON_B,
    BUTTON_X,
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_LEFT,
    BUTTON_RIGHT,
    BUTTON_LB,
    BUTTON_RB,
    BUTTON_START,
    BUTTON_BACK,
    BUTTON_LP,
    BUTTON_RP,
    MAX_BTN
} CONTROLLER_BUTTON;

class JoyStickManager : public QObject
{
    Q_OBJECT
public:
    explicit JoyStickManager(QObject *parent = nullptr);


private:
    TYPE_CONTROLLER typeCon;
    JoyThread *joy;

signals:
    void onLeftAxisXChanged(int);
    void onLeftAxisYChanged(int);
    void onRightAxisYChanged(int);
    void onRightAxisXChanged(int);
    void onLTRTChanged(int);
    void onLTChanged(int);
    void onRTChanged(int);
    void onButtonRBChanged(bool);
    void onButtonLBChanged(bool);
    void onButtonUpChanged(bool);
    void onButtonRightChanged(bool);
    void onButtonDownChanged(bool);
    void onButtonLeftChanged(bool);
    void onButtonAChanged(bool);
    void onButtonBChanged(bool);
    void onButtonXChanged(bool);
    void onButtonYChanged(bool);
    void onButtonLPChanged(bool);
    void onButtonRPChanged(bool);
    void onButtonStartChanged(bool);
    void onButtonBackChanged(bool);



};

#endif // JOYSTICKMANAGER_H
