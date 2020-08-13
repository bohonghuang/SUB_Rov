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
    initCommand();
}

quint8 *SendManager::getCommand()
{
    return this->command;
}

void SendManager::Deep(int v)
{
    if(v == 0)
        this->command[3] = Deep_Lock;
    if(v == 1)
        this->command[3] = Deep_Lock;
    if(v == 2)
        this->command[3] = Deep_Unlock;

    emit deepChanged();
    emit commandChanged();
}

void SendManager::Direction(int v)
{
    if(v == 0)
        this->command[4] = Direction_Lock;
    if(v == 1)
        this->command[4] = Direction_Lock;
    if(v == 2)
        this->command[4] = Direction_Unlock;

    emit directChanged();
    emit commandChanged();
}

void SendManager::ForwordBack(quint8 v)
{
    this->command[5] = v;
    emit commandChanged();
}

void SendManager::LeftRight(quint8 v)
{
    this->command[6] = v;
    emit commandChanged();
}

void SendManager::UpDown(int v)
{
    if(v == 0)
        this->command[7] = UpDown_Normal_Value;
    if(v >= 1)
        this->command[7] = Up_Value;
    if(v <= -1)
        this->command[7] = Down_Value;

    emit commandChanged();
}

void SendManager::Spin(int v)
{
    if(v == 0)
        this->command[8] = Spin_Normal_Value;
    if(v >= 1)
        this->command[8] = Spin_Left_Value;
    if(v <= -1)
        this->command[8] = Spin_Right_Value;
    emit commandChanged();
}

void SendManager::Oil(int v)
{
    int t = this->command[9];
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

    this->command[9] = (quint8) t;
    emit commandChanged();

}

void SendManager::Light(int v)
{
    if(v == 0)
        this->command[10] = Light_Normal;
    if(v >= 1)
        this->command[10] = Light_Up;
    if(v <= -1)
        this->command[10] = Light_Down;
    emit commandChanged();
}

void SendManager::Cloud(int v)
{
    if(v == 0)
        this->command[11] = Cloud_Normal;
    if(v >= 1)
        this->command[11] = Cloud_Up;
    if(v <= -1)
        this->command[11] = Cloud_Down;
    emit commandChanged();
}

void SendManager::Camera(quint8 v)
{
    this->command[12] = v;
    emit commandChanged();
}

void SendManager::Manipulator(int v)
{
    if(v == 0)
        this->command[8] = Manipulator_Normal;
    if(v >= 1)
        this->command[8] = Manipulator_Open;
    if(v <= -1)
        this->command[8] = Manipulator_Close;
    emit commandChanged();
}

void SendManager::DeviceSwitch(int v)
{
    if(v == 0)
        this->command[8] = Start_Stop_Normal;
    if(v >= 1)
        this->command[8] = Start_Value;
    if(v <= -1)
        this->command[8] = Stop_Value;
    emit commandChanged();
}
