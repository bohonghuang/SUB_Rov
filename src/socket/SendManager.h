#ifndef SENDMANAGER_H
#define SENDMANAGER_H

#define UpDown_Normal_value 0x00
#define Spin_Normal_value 0x00

#define Forwardback_Normal_value 0x80
#define LeftRight_Normal_value 0x80

#define To_Spin_Left_value 0x01
#define To_Spin_Right_value 0x02
#define To_Up_value 0x01
#define To_Down_value 0x02
#define To_Forward_value 0x01
#define To_Back_value 0x01
//方向锁定
#define To_Direction_Lock 0x01
#define To_Direction_Unlock 0x02
//深度锁定
#define To_Deep_Lock 0x01
#define To_Deep_Unlock 0x02
//紧急制动
#define To_Device_Status_Normal 0x00
#define To_Device_Status_On 0x01
#define To_Device_Status_Off 0x02

//灯光控制
#define To_Normal_Light 0x00
//变亮
#define To_Up_Light 0x01
//变暗
#define To_Down_Light 0x02

//相机控制
#define To_Camera_Normal 0x00
#define To_Camera_Focus_Large 0x01
#define To_Camera_Focus_Small 0x02
#define To_Camera_Zoom_Large 0x11
#define To_Camera_Zoom_Small 0x12

//云台控制
#define To_Cloud_Normal 0x00
#define To_Cloud_Up 0x01
#define To_Cloud_Down 0x02
#define To_Cloud_Central 0x03

//机器手控制
#define To_Machine_Normal 0x00
#define To_Machine_Open 0x01
#define To_Machine_Close 0x02



#include <QObject>
#include "SendCommand.h"
#include <QDir>
#include <QDebug>

#include "src/robot/Oilvalve.h"

class SendManager : public QObject
{
    Q_OBJECT
public:
    explicit SendManager(QObject *parent = nullptr);
    QString toString();
public:
    SendCommand sendcmd;
    Oilvalve oil;
    QDir dir;
    QString rootPath;
    QString logoPath;
    QString logo;
public:
    void Display();
    void DelayDisplay(QObject obj);
    void ThreadStart();
    //
    void ToUp();
    void ToDown();
    void ToLeftSpin();
    void ToRightSpin();
    //
    void ToAllNormal();
    //
    void ToSpinNormal();
    void ToUpDownNormal();
    void ToLeftRightNormal();
    void ToForwar_back_Normal();
    //
    void SetLeftOrRight(uchar);
    void SetForwardOrBack(uchar);
    //
    void TurnLightUp();
    void TurnLightDown();
    void TurnNormalLight();
    void AddOil();
    void SubOil();
    //
    void TurnCamera();
    void TurnCameraNormal();
    void TurnCameraFocusingToLarge();
    void TurnCameraFocusingToSmall();
    void TurnCameraZoomToLarge();
    void TurnCameraZoomToSmall();
    //
    void TurnCloudUp();
    void TurnCloudDown();
    void TurnCloudCentral();
    void TurnCloudNormal();

    void TurnMachineNormal();
    void TurnMachineOpen();
    void TurnMachineClose();

    void TurnDirectionLock();
    void TurnDeepLock();

    void TurnOn();
    void TurnOff();
    void TurnDeviceNormal();

    void SendCommandReset();

    quint8* udpCommand();
    quint8 getCheck();
    QByteArray getBytearrayCommand();
signals:

};

#endif // SENDMANAGER_H
