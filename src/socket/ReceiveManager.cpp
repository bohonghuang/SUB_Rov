#include "ReceiveManager.h"
#include <QDebug>
#include <QtMath>

ReceiveManager::ReceiveManager(QObject *parent) : QObject(parent)
{
    this->receive = ReceiveCommand();
}

///
/// \brief ReceiveManager::IsTrueCommand
/// \param data 传入的一个quint8 数组类型
/// \return true代表核验成功，false核验失败
/// 用来核验数据内容是否为真实内容
bool ReceiveManager::isTrueCommand(quint8* data){


    int length = _msize(data) / sizeof (quint8);

    if( data == nullptr )
        return false;

    if(length < 25)
        return false;

    if(data[0]!=0xAA && data[1] != 0x55 && data[2] != 0x16)
        return false;


    quint8 result = 0;
    int sum = 0;
    int i = 0;

    for( i=0; i< length - 1 ; i++){
        sum += data[i];
    }
    result = sum & 0xffff;

    if(result == data[i])
        return true;
    else
        return false;
}

bool ReceiveManager::isTrueCommand(QByteArray cmd)
{
    int length = cmd.size();
    if(length < 25 )
        return false;

    quint8 buffer[26];
    memcpy(&buffer, cmd, length);


    return isTrueCommand(buffer);
}

///
/// \brief ReceiveManager::UpdateCommand
/// \param cmd 传入的一个quint8数组
/// 根据传入的cmd进行数据更新
void ReceiveManager::updateCommand(quint8* cmd){

    if(isTrueCommand(cmd)){
        receive.head_1 = cmd[0];
        receive.head_2 = cmd[1];
        receive.head_3 = cmd[2];

        receive.electric_1 = cmd[3];
        receive.electric_2 = cmd[4];

        receive.temperatureOutside_1 = cmd[5];
        receive.temperatureOutside_2 = cmd[6];

        receive.temperatureInside_1 = cmd[7];
        receive.temperatureInside_2 = cmd[8];

        receive.deep_1 = cmd[9];
        receive.deep_2 = cmd[10];
        receive.deep_3 = cmd[11];

        receive.yaw_1 = cmd[12];
        receive.yaw_2 = cmd[13];

        receive.pitch_1 = cmd[14];
        receive.pitch_2 = cmd[15];

        receive.roll_1 = cmd[16];
        receive.roll_2 = cmd[17];

        receive.speed = cmd[18];

        receive.deviceStatusTag = cmd[19];

        receive.status = cmd[20];

        receive.current_1 = cmd[21];
        receive.current_2 = cmd[22];

        receive.keep_1 = cmd[23];
        receive.keep_2 = cmd[24];

        receive.check = cmd[26];
    }


}

void ReceiveManager::updateCommand(QByteArray cmd)
{
    if(isTrueCommand(cmd)){
        quint8 buffer[26];
        int length = cmd.size();
        memcpy(&buffer, cmd, length);
        updateCommand(buffer);
    }
}


///
/// \brief ReceiveManager::GetAngle
/// \param high
/// \param low
/// \return double类型
/// 获取角度
double ReceiveManager::GetAngle(quint8 high, quint8 low)
{
    int sum = 0;

    for( int i=0; i<8; i++){
        sum += (GetBit(low, i+1) * qPow(2,i));
    }
    for(int i=0; i<8; i++){
        sum += (GetBit(high, i+1) * qPow(2, i+8));
    }
    double result = ((double)sum) / 100.0 - 180;
    return result;
}

///
/// \brief ReceiveManager::GetCalcAngle
/// \param high
/// \param low
/// \return float类型
/// 获取一个角度
float ReceiveManager::GetCalcAngle(quint8 high, quint8 low)
{
    int sum = 0;

    for( int i=0; i<8; i++){
        sum += (int)(GetBit(low, i+1)
                     * qPow(2,i));
    }
    for(int i=0; i<8; i++){
        sum += (int)(GetBit(high, i+1)
                     * qPow(2, i+8));
    }
    sum -= (int) (GetBit(high, 8)
                  * qPow(2, 15));
    float tmp = (float) sum;
    float result = tmp/32768*180;

    return result;
}


///
/// \brief ReceiveManager::GetBit
/// \param num 待取出数字
/// \param pos 位置索引
/// \return 取出的数字
/// 取num的二进制下第i位， i从1开始
int ReceiveManager::GetBit(quint8 num, quint8 pos){
    quint8 tmp = num >> (pos - 1);
    return tmp & 0x01;;
}

///
/// \brief ReceiveManager::getDeep
/// \return  单位：??
///
int ReceiveManager::getDeep()
{
    // high最高为符号位，若为1，则为负数
    int high = receive.deep_1;
    int middle = receive.deep_2;
    int low = receive.deep_3;
    int result = (int)(( 0 | (high << 16) | (middle << 8) | low));

    return result;
}
///
/// \brief ReceiveManager::getVoltage 电压
/// \return
///
double ReceiveManager::getVoltage()
{
    double volH, volL;
    volH = receive.electric_1;
    volL = receive.electric_2;

    double ti = volL / 100 + volH;

    return ti;
}

///
/// \brief ReceiveManager::getCurrent 电流
/// \return
///
double ReceiveManager::getCurrent()
{
    double curH,curL;
    curH = receive.current_1;
    curL = receive.current_2;

    double t = curH + (curL / 100);
    return t;
}

///
/// \brief ReceiveManager::getSpeed 速度
/// \return
///
float ReceiveManager::getSpeed()
{
    float tp =  ((float)receive.speed) / 10;
    return tp;
}

bool ReceiveManager::getRovStatus()
{
    if(receive.status == 0x00 || receive.status == 0x02)
        return false;
    else
        return true;
}

int ReceiveManager::getRovDeviceStatus()
{
    switch (receive.deviceStatusTag) {

    default:
        break;
    }
}

///
/// \brief ReceiveManager::getPower 功率
/// \return
///
double ReceiveManager::getPower()
{
    double tv = getVoltage();
    double ti = getCurrent();
    double tp = tv * ti;

    return tp;
}


///
/// \brief ReceiveManager::getTemperatureInside 内温
/// \return
///
double ReceiveManager::getTemperatureInside()
{
    double tempH = receive.temperatureInside_1;
    double tempL = receive.temperatureInside_2;
    double tmp = tempL / 100 + tempH;

    return tmp;
}

///
/// \brief ReceiveManager::getTemperatureOutside 外温
/// \return
///
double ReceiveManager::getTemperatureOutside()
{
    double tempH = receive.temperatureOutside_1;
    double tempL = receive.temperatureOutside_2;
    double tmp = tempL / 100 + tempH;

    return tmp;
}

///
/// \brief ReceiveManager::getYaw 航向角
/// \return
///
double ReceiveManager::getYaw()
{
    double yaw = GetAngle(receive.yaw_1, receive.yaw_2);

    return yaw;
}

///
/// \brief ReceiveManager::getPitch 俯仰
/// \return
///
double ReceiveManager::getPitch()
{
    double pitch = GetAngle(receive.pitch_1, receive.pitch_2);

    return pitch;
}

///
/// \brief ReceiveManager::getRoll 横滚角
/// \return
///
double ReceiveManager::getRoll()
{
    double roll = GetAngle(receive.roll_1, receive.roll_2);

    return roll;
}


