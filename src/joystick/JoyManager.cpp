#include "JoyManager.h"
#include <QDebug>
#include "VideoManager.h"

JoyManager::JoyManager(QObject * parent ) : QObject(parent)
{

    this->connected = false;
    this->init();
}

JoyManager::~JoyManager(){
}

void JoyManager::init(){

    this->instance = QJoysticks::getInstance();
    this->instance->setVirtualJoystickRange(1);
    this->instance->setVirtualJoystickEnabled(true);

}

void JoyManager::send(){

}
void JoyManager::onInformationChanged(){
    this->send();
}

void JoyManager::handle_joystick_aciton_axis(int index, double value)
{
    qDebug() << "handle_joystick_aciton_axis";
    switch (index) {
    case 0:
        rovApp()->getToolbox()->getRovControlCore()->do_Forward_Back_Change(value);
        break;
    case 1:
        rovApp()->getToolbox()->getRovControlCore()->do_Left_Right_Change(value);
        break;
    case 2:
        doCamera(1, value);
        break;
    case 4:
        doCamera(0, value);
        break;
    default:
        qWarning() << "error of axis - index";
        //return ;
    }
}

void JoyManager::handle_joystick_aciton_button(int index, bool value)
{
    switch (index) {
    case 0 : //y 开灯
        if( value )
            rovApp()->getToolbox()->getRovControlCore()->doTurnLightUp();
        else
            rovApp()->getToolbox()->getRovControlCore()->doTurnLightNormal();
        break;
    case 1 : //b 开机器手
        if( value )
            rovApp()->getToolbox()->getRovControlCore()->doTurnMachineOpen();
        else
            rovApp()->getToolbox()->getRovControlCore()->doTurnMachineNormal();
        break;
    case 2 : //a 关灯
        if( value )
            rovApp()->getToolbox()->getRovControlCore()->doTurnLightDown();
        else
            rovApp()->getToolbox()->getRovControlCore()->doTurnLightNormal();
        break;
    case 3 : //x 关机器手
        if( value )
            rovApp()->getToolbox()->getRovControlCore()->doTurnMachineClose();
        else
            rovApp()->getToolbox()->getRovControlCore()->doTurnMachineNormal();
        break;
    case 4 : //lb 左旋
        if( value )
            rovApp()->getToolbox()->getRovControlCore()->doSpinLeft();
        else
            rovApp()->getToolbox()->getRovControlCore()->doStopSpin();
        break;
    case 5 : //rb 右旋
        if( value )
            rovApp()->getToolbox()->getRovControlCore()->doSpinRight();
        else
            rovApp()->getToolbox()->getRovControlCore()->doStopSpin();
        break;
    case 6 : //lt 下降
        if( value )
            rovApp()->getToolbox()->getRovControlCore()->doTurnDown();
        else
            rovApp()->getToolbox()->getRovControlCore()->doStopUpDown();
        break;
    case 7 : //rt 上升
        if( value )
            rovApp()->getToolbox()->getRovControlCore()->doTurnUp();
        else
            rovApp()->getToolbox()->getRovControlCore()->doStopUpDown();
        break;
    case 8 : //back 深锁
        if( value )
            rovApp()->getToolbox()->getRovControlCore()->doLockDeep();
        break;
    case 9 : //start 方向锁
        if( value )
            rovApp()->getToolbox()->getRovControlCore()->doLockDirection();
        break;
    default:
        qWarning() << "error of axis - index";
        //return ;
    }
}

void JoyManager::handle_joystick_aciton_povs(int value)
{
    switch (value) {
    case 0: //上 加油
        rovApp()->getToolbox()->getRovControlCore()->doAddOil();
        break;
    case 45:

        break;
    case 90: //右  云台
        rovApp()->getToolbox()->getRovControlCore()->doTurnCloudUp();
        break;
    case 135:
        break;
    case 180:
        rovApp()->getToolbox()->getRovControlCore()->doSubOil();
        break;
    case 225:
        break;
    case 270:
        rovApp()->getToolbox()->getRovControlCore()->doTurnCloudDown();
        break;
    case 315:
        break;
    default:
        rovApp()->getToolbox()->getRovControlCore()->doTurnCloudNormal();
    }
}


void JoyManager::doCamera(int index, double value)
{
    if( index == 0 ){
        if( value > 0.5)
            rovApp()->getToolbox()->getRovControlCore()->doCameraFocusingToLarge();
        else if( value < 0.5 ) {
            rovApp()->getToolbox()->getRovControlCore()->doCameraFocusingToSmall();
        }
        else {
            rovApp()->getToolbox()->getRovControlCore()->doCameraNormal();
        }
    }
    if( index == 1){
        if( value > 0){
            rovApp()->getToolbox()->getRovControlCore()->doCameraZoomingToLarge();
        }
        else if( value < 0){
            rovApp()->getToolbox()->getRovControlCore()->doCameraZoomingToSmall();
        }
        else {
            rovApp()->getToolbox()->getRovControlCore()->doCameraNormal();
        }
    }
}




