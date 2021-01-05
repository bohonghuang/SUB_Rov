#include "SendManager.h"

#define UpDown_Normal_Value 0x00
#define Spin_Normal_Value 0x00

#define Forwardback_Normal_Value 0x80
#define LeftRight_Normal_Value 0x80

#define Spin_Left_Value 0x01
#define Spin_Right_Value 0x02
#define Up_Value 0x01
#define Down_Value 0x02
#define Forward_Value 0x01
#define Back_Value 0x01
//方向锁定
#define Direction_Lock 0x01
#define Direction_Unlock 0x02
//深度锁定
#define Deep_Lock 0x01
#define Deep_Unlock 0x02
//紧急制动
#define Device_Status_Normal 0x00
#define Device_Status_On 0x01
#define Device_Status_Off 0x02

//灯光控制
#define Light_Normal 0x00
//变亮
#define Light_Up 0x01
//变暗
#define Light_Down 0x02

//相机控制
#define Camera_Normal 0x00
#define Camera_Focus_Enlarge 0x01
#define Camera_Focus_Reduce 0x02
#define Camera_Zoom_Enlarge 0x11
#define Camera_Zoom_Reduce 0x12

//云台控制
#define Cloud_Normal 0x00
#define Cloud_Up 0x01
#define Cloud_Down 0x02
#define Cloud_Central 0x03

//机器手控制
#define Manipulator_Normal 0x00
#define Manipulator_Open 0x01
#define Manipulator_Close 0x02

//启动停止位
#define Start_Value 0x01
#define Stop_Value 0x02
#define Start_Stop_Normal 0x00

//速度挡位：
#define Speed_None 0x00
#define Speed_First 0x19
#define Speed_Second 0x5a
#define Speed_Third 0x82
#define Speed_Forth 0xB4
#define Speed_Fifth 0xff

//吸取器
#define Draw_Open 0x01
#define Draw_Close 0x02
#define Draw_Normal 0x00

void SendManager::initCommand()
{
    maxLength = 20;
    this->command = new quint8[maxLength]{
        0xAA, 0x55, 0x10, Deep_Lock, Direction_Lock,
        Forwardback_Normal_Value, LeftRight_Normal_Value,
        UpDown_Normal_Value, Spin_Normal_Value,
        Speed_None, Light_Normal, Camera_Normal, Cloud_Normal,
        Manipulator_Normal, 0x00, Draw_Normal, 0x00, 0x00,
        Start_Stop_Normal
    };

}

SendManager::SendManager(QObject *parent) : QObject(parent)
{
    this->log = new SendLogging;
    initCommand();
}

quint8 *SendManager::getCommand()
{
    return this->command;
}

int SendManager::getCommandLength()
{
    return this->maxLength;
}

bool SendManager::isDeepLocked()
{
    if( this->command[3] == Deep_Unlock)
        return false;
    else
        return true;
}

bool SendManager::isDirectLocked()
{
    if( this->command[4] == Direction_Unlock)
        return false;
    else
        return true;
}

void SendManager::Deep(int v)
{
    int index = 3;
    quint8 temp = command[index];
    if(v == 0)
        this->command[index] = Deep_Lock ;
    if(v == 1)
        this->command[index] = Deep_Lock;
    if(v == 2)
        this->command[index] = Deep_Unlock;

    emit deepChanged();

    if( temp != command[index])
        emit commandChanged();
}

void SendManager::Direction(int v)
{
    int index = 4;
    quint8 temp = command[index];
    if(v == 0)
        this->command[index] = Direction_Lock;
    if(v == 1)
        this->command[index] = Direction_Lock;
    if(v == 2)
        this->command[index] = Direction_Unlock;

    emit directChanged();
    if( temp != command[index])
        emit commandChanged();
}

void SendManager::ForwordBack(quint8 v)
{
    int index = 5;
    quint8 temp = command[index];

    this->command[index] = v;

    if( temp != command[index])
        emit commandChanged();
}

void SendManager::LeftRight(quint8 v)
{
    int index = 6;
    quint8 temp = command[index];

    this->command[index] = v;

    if( temp != command[index])
        emit commandChanged();
}

void SendManager::newUpDown(quint8 v)
{
    int index = 7;
    quint8 temp = command[index];

    this->command[index] = v;

    if( temp != command[index])
        emit commandChanged();
}

void SendManager::UpDown(int v)
{
    int index = 7;
    quint8 temp = command[index];
    if(v == 0)
        this->command[index] = UpDown_Normal_Value;
    if(v >= 1)
        this->command[index] = Up_Value;
    if(v <= -1)
        this->command[index] = Down_Value;

    if( temp != command[index])
        emit commandChanged();
}

void SendManager::newSpin(quint8 v)
{
    int index = 8;
    quint8 temp = command[index];

    this->command[index] = v;

    if( temp != command[index])
        emit commandChanged();
}

void SendManager::Spin(int v)
{
    int index = 8;
    quint8 temp = command[index];
    if(v == 0)
        this->command[index] = Spin_Normal_Value;
    if(v >= 1)
        this->command[index] = Spin_Left_Value;
    if(v <= -1)
        this->command[index] = Spin_Right_Value;

    if( temp != command[index])
        emit commandChanged();
}

void SendManager::Oil(int v)
{
    int index = 9;
    quint8 temp = command[index];
    int t = this->command[index];
    if(v >= 1){
        t += 30;
        if(t>255)
            t = 255;
    }
    if( v <= -1){
        t -= 30;
        if(t<0)
            t = 0;
    }

    this->command[index] = (quint8) t;

    if( temp != command[index])
        emit commandChanged();

}

void SendManager::Light(int v)
{
    int index = 10;
    quint8 temp = command[index];
    if(v == 0)
        this->command[index] = Light_Normal;
    if(v >= 1)
        this->command[index] = Light_Up;
    if(v <= -1)
        this->command[index] = Light_Down;
    if( temp != command[index])
        emit commandChanged();
}

//#include <QDebug>
void SendManager::Camera(quint8 v)
{
    int index  = 11;
    quint8 temp = command[index];
//    qDebug() << v;
    this->command[index] = v;
//    if( temp != command[index])
        emit commandChanged();
}

void SendManager::Cloud(int v)
{
    int index = 12;
    quint8 temp = command[index];
    if(v == 0)
        this->command[index] = Cloud_Normal;
    if(v >= 1)
        this->command[index] = Cloud_Up;
    if(v <= -1)
        this->command[index] = Cloud_Down;
    if( temp != command[index])
        emit commandChanged();
}

void SendManager::Manipulator(int v)
{
    int index = 13;
    quint8 temp = command[index];
    if(v == 0)
        this->command[index] = Manipulator_Normal;
    if(v >= 1)
        this->command[index] = Manipulator_Open;
    if(v <= -1)
        this->command[index] = Manipulator_Close;
    if( temp != command[index])
        emit commandChanged();
}

void SendManager::DeviceSwitch(int v)
{
    int index = 18;
    quint8 temp = command[index];
    if(v == 0)
        this->command[index] = Start_Stop_Normal;
    if(v >= 1)
        this->command[index] = Start_Value;
    if(v <= -1)
        this->command[index] = Stop_Value;
    if( temp != command[index])
        emit commandChanged();
}

void SendManager::TurnDevice()
{
    int index = 18;
    quint8 temp = command[index];

    if ( temp == 0 ){
        DeviceSwitch(-1);
    }
    else if( temp == 0x01 ){
        DeviceSwitch(-1);
    }
    else if( temp == 0x02 ){
        DeviceSwitch(1);
    }
}
