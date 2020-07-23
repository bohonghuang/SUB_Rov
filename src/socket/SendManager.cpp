#include "SendManager.h"

SendManager::SendManager(QObject *parent)
    : QObject(parent)
{
    qDebug("SendManager: Create SendManager.");

    this->oil = Oilvalve();
    this->sendcmd = SendCommand();
    rootPath = dir.currentPath();
    qDebug("SendManager: Create complete.");
}

QString SendManager::toString()
{
    return QString();
}

///
/// \brief SendManager::TurnMachineNormal
/// Machine的一般状态
void SendManager::TurnMachineNormal(){
    this->sendcmd.machine = To_Machine_Normal;

}

void SendManager::TurnMachineOpen()
{
    this->sendcmd.machine = To_Machine_Open;
}
void SendManager::TurnMachineClose(){
    this->sendcmd.machine = To_Machine_Close;
}



///
/// \brief SendManager::TurnCameraFocusingToLarge
/// 聚焦放大
void SendManager::TurnCameraFocusingToLarge(){
    this->sendcmd.camera = To_Camera_Focus_Large;
}
///
/// \brief SendManager::TurnCameraFocusingToSmall
/// 聚焦缩小
void SendManager::TurnCameraFocusingToSmall(){
    this->sendcmd.camera = To_Camera_Focus_Small;
}
///
/// \brief SendManager::TurnCameroZoomToLarge
/// 变焦放大
void SendManager::TurnCameraZoomToLarge(){
    this->sendcmd.camera = To_Camera_Zoom_Large;
}
///
/// \brief SendManager::TurnCameroZoomToSmall
/// 变焦缩小
void SendManager::TurnCameraZoomToSmall(){
    this->sendcmd.camera = To_Camera_Zoom_Small;
}

///
/// \brief SendManager::TurnCameraNormal
/// 相机的变化停止，保持当前状态
void SendManager::TurnCameraNormal(){
    this->sendcmd.camera = To_Camera_Normal;
}


//-------------云台控制---------------//

void SendManager::TurnCloudUp()
{
    this->sendcmd.cloud = To_Cloud_Up;
}

void SendManager::TurnCloudDown()
{
    this->sendcmd.cloud = To_Cloud_Down;
}

void SendManager::TurnCloudCentral()
{
    this->sendcmd.cloud = To_Cloud_Central;
}
///
/// \brief SendManager::TurnCloudNormal
///  云台的一般状态
void SendManager::TurnCloudNormal(){
    this->sendcmd.cloud = To_Cloud_Normal;
}



///
/// \brief SendManager::ToNormal
/// 在左右、上下、前后上恢复到一般状态
void SendManager::ToAllNormal(){
    ToUpDownNormal();
    ToSpinNormal();
    ToLeftRightNormal();
    ToForwar_back_Normal();
    TurnCloudNormal();
    TurnNormalLight();
    TurnCameraNormal();
    TurnDeviceNormal();
    TurnMachineNormal();
}



/********************************/
/*****|一些关于方向控制的方法|******/
/********************************/

///
/// \brief SendManager::ToDown
/// 俯降
void SendManager::ToDown(){
    this->sendcmd.up_down
            = To_Down_value;
}

///
/// \brief SendManager::ToUp
/// 拉升
void SendManager::ToUp(){
    this->sendcmd.up_down
            = To_Up_value;
}


///
/// \brief SendManager::ToUpDownNormal
/// 上下状态恢复到一般状态
void SendManager::ToUpDownNormal(){
    this->sendcmd.up_down
            = UpDown_Normal_value;
}



///
/// \brief SendManager::ToLeftRightNormal
/// 左右状态恢复到一般状态
void SendManager::ToLeftRightNormal(){
    this->sendcmd.left_right
            = LeftRight_Normal_value;
}


///
/// \brief SendManager::ToLeftSpin
/// 左旋
void SendManager::ToLeftSpin(){
    this->sendcmd.spin
            = To_Spin_Left_value;
}


///
/// \brief SendManager::ToRightSpin
/// 右旋
void SendManager::ToRightSpin(){
    this->sendcmd.spin
            = To_Spin_Right_value;
}

///
/// \brief SendManager::ToSpinNormal
/// 旋转状态恢复到一般状态
void SendManager::ToSpinNormal(){
    this->sendcmd.spin
            = Spin_Normal_value;
}



///
/// \brief SendManager::ToForwar_back_Normal
/// 前后状态恢复到一般状态
void SendManager::ToForwar_back_Normal(){
    this->sendcmd.forward_backward
            = Forwardback_Normal_value;
}

void SendManager::SetLeftOrRight(uchar c)
{
    this->sendcmd.forward_backward = c;
}

void SendManager::SetForwardOrBack(uchar c)
{
    this->sendcmd.forward_backward = c;
}


//-------------灯光----------------//
void SendManager::TurnLightUp()
{
    this->sendcmd.light = To_Up_Light;
}
void SendManager::TurnLightDown(){
    this->sendcmd.light = To_Down_Light;
}
void SendManager::TurnNormalLight(){
    this->sendcmd.light = To_Normal_Light;
}


/***********************************/


///
/// \brief SendManager::TurnCamera
/// 摄像头的开闭
void SendManager::TurnCamera(){

}
///
/// \brief SendManager::GetCommand
/// \return 一个指令集的数组的指针
/// 获取一串指令集。
/// 在该方法中做了一个 [] --> * 的操作
quint8* SendManager::udpCommand(){
    quint8* cmd = (quint8*)malloc(sizeof (quint8) * 20);

    cmd[0] = this->sendcmd.head_1;
    cmd[1] = this->sendcmd.head_2;
    cmd[2] = this->sendcmd.head_length;
    cmd[3] = this->sendcmd.deeplock;
    cmd[4] = this->sendcmd.directionlock;
    cmd[5] = this->sendcmd.forward_backward;
    cmd[6] = this->sendcmd.left_right;
    cmd[7] = this->sendcmd.up_down;
    cmd[8] = this->sendcmd.spin;
    cmd[9] = this->sendcmd.oil;
    cmd[10] = this->sendcmd.light;
    cmd[11] = this->sendcmd.camera;
    cmd[12] = this->sendcmd.cloud;
    cmd[13] = this->sendcmd.machine;
    cmd[14] = this->sendcmd.startPi;
    cmd[15] = this->sendcmd.draw;
    cmd[16] = this->sendcmd.keep_1;
    cmd[17] = this->sendcmd.keep_2;
    cmd[18] = this->sendcmd.status;
    cmd[19] = getCheck();

    return cmd;
}


///
/// \brief SendManager::GetCheck
/// \return 一个0-255的值
/// 这是一个核检方法，他能返回一个检查码。
quint8 SendManager::getCheck(){
    quint8 temp;

    qDebug("SendManager::get_check() In");
    temp = (unsigned char)(
                  this->sendcmd.head_1
                + this->sendcmd.head_2
                + this->sendcmd.head_length
                + this->sendcmd.deeplock
                + this->sendcmd.directionlock
                + this->sendcmd.forward_backward
                + this->sendcmd.left_right
                + this->sendcmd.up_down
                + this->sendcmd.spin
                + this->sendcmd.oil
                + this->sendcmd.light
                + this->sendcmd.camera
                + this->sendcmd.cloud
                + this->sendcmd.machine
                + this->sendcmd.keep_1
                + this->sendcmd.keep_2
                + this->sendcmd.draw
                + this->sendcmd.startPi
                + this->sendcmd.status)
                & (0xFF);
    qDebug() << " check get == " + QString(temp) ;

    qDebug("SendManager::get_check() Out");
    return temp;
}

QByteArray SendManager::getBytearrayCommand()
{
    quint8* t = udpCommand();
    QByteArray b;
    int length = _msize( t) / sizeof (quint8);
    b.resize(length);
    memcpy(b.data(), t, length);

    return b;
}

///
/// \brief SendManager::SendCommandReset
/// 对sendcmd的部分数值进行了重置
void SendManager::SendCommandReset(){
    qDebug("SendManager::SendCommandReset() In");

    this->ToAllNormal();
    qDebug("SendManager::SendCommandReset() Out");

}


///
/// \brief SendManager::TurnDirectionLock
/// 方向锁定
void SendManager::TurnDirectionLock(){
    qDebug("SendManager::TurnDirectionLock() In");
    qDebug() << "send cmd -> direction Lock == " + QString(sendcmd.directionlock) ;

    if(this->sendcmd.directionlock == To_Direction_Lock )
        this->sendcmd.directionlock = To_Direction_Unlock;
    else
        this->sendcmd.directionlock = To_Direction_Lock;
    qDebug("SendManager::TurnDirectionLock() Out");
}

///
/// \brief SendManager::TurnDeepLock
/// 深度锁定
void SendManager::TurnDeepLock(){
    qDebug("SendManager::TurnDeepLock() In");
    qDebug() << "send cmd -> deeplock == " + QString(sendcmd.deeplock) ;

    if(this->sendcmd.deeplock == To_Deep_Lock)
        this->sendcmd.deeplock = To_Deep_Unlock;
    else
        this->sendcmd.deeplock = To_Deep_Lock;


    qDebug("SendManager::TurnDeepLock() Out");
}

///
/// \brief SendManager::TurnKeep_5
/// 启动
#include <QDebug>
void SendManager::TurnOn(){
    qDebug("SendManager::TurnOn() In");
    qDebug() << "send cmd -> status == " + QString(sendcmd.status) ;
    if(this->sendcmd.status == To_Device_Status_Normal || sendcmd.status == To_Device_Status_Off)
        this->sendcmd.status = To_Device_Status_On;
    qDebug("SendManager::TurnOn() Out");
}

void SendManager::TurnOff()
{
    qDebug("SendManager::TurnOff() In");
    qDebug() << "send cmd -> status == " + QString(sendcmd.status) ;
    if(this->sendcmd.status == To_Device_Status_On)
        this->sendcmd.status = To_Device_Status_Off;
    qDebug("SendManager::TurnOff() Out");

}

void SendManager::TurnDeviceNormal(){
    qDebug("SendManager::TurnDeviceNormal() In");
    qDebug() << "send cmd -> status == " + QString(sendcmd.status) ;

    this->sendcmd.status = To_Device_Status_Normal;
    qDebug("SendManager::TurnDeviceNormal() Out");
}
///
/// \brief SendManager::AddOil
/// 这个方法中对oil进行了“加油”操作，
/// 并将新的值赋给了成员sendcmd模型之中
void SendManager::AddOil(){
    qDebug("SendManager::AddOil() In");
    qDebug() << "send cmd -> oil == " + QString(sendcmd.oil) ;

    this->sendcmd.oil = this->oil.GetOilAddLevelAndOfIndex();
    qDebug("SendManager::AddOil() Out");
}

///
/// \brief SendManager::SubOil
/// 这里做的是减速操作
/// 并将新的值赋给了成员sendcmd模型之中
void SendManager::SubOil(){
    qDebug("SendManager::SubOil() In");
    qDebug() << "send cmd -> oil == " + QString(sendcmd.oil) ;

    this->sendcmd.oil = this->oil.GetOilSubOilAndOfIndex();
    qDebug("SendManager::SubOil() Out");
}
