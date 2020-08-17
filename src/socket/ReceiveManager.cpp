#include "ReceiveManager.h"
#include <QtMath>

#include "../RovApplication.h"
#include "../Settings/SettingsManager.h"
#include <RovToolbox.h>

void ReceiveManager::initCommand()
{
    this->maxLength = 26;
    this->command = new quint8[maxLength];
    for( int i=0; i<maxLength; i++ ){
        this->command[i] = 0x00;
    }

    log->info("init receive CMD: " + getCommandOfInt());
    connect(this, &ReceiveManager::commandChanged, this, [=]{
        QString str = "CMD: ";
        for( int i=0; i<maxLength; i++){
            str += " " + QString::number(command[i]);
        }
        log->info(str);
    });
}

QString ReceiveManager::getCommandOfInt()
{
    QString str = "";
    for( int i=0; i<maxLength; i++ ){
        str += QStringLiteral(" %1 ").arg(this->command[i]);
    }
    return str;
}

int ReceiveManager::getBit(quint8 num, int pos)
{
    quint8 tmp =  num >> (pos);
    return tmp & 0x01;
}

double ReceiveManager::getAngle(quint8 high, quint8 low)
{
    int sum = 0;
    for( int i=0; i<8; i++)
        sum += (getBit(low, i+1) * qPow(2, i));
    for( int i=0; i<8; i++)
        sum += (getBit(high, i+1) * qPow(2, i + 8));
    double result = ((double) sum ) /100.0 - 180;
    return result;
}

ReceiveManager::ReceiveManager(QObject *parent) : QObject(parent)
{
    this->log = new ReceiveLogging;
    initCommand();
}

bool ReceiveManager::checkout(quint8 *nc)
{
    return checkout(nc, maxLength);
}

bool ReceiveManager::checkout(quint8 *nc, int length)
{
    bool enableCheckout =
            rovApp()->getToolbox()->getSettingsManager()->isEnableCheckout();
    if( !enableCheckout ){
        return true;
    }

    if( nc == nullptr){
        log->warning("param newCommand is null!!");
        return false;
    }
    if( length<25 ){
        log->warning("Length is a error number: " + QString(length));
        return false;
    }
    if( nc[0] != 0xAA && nc[1] != 0x55 && nc[2] != 0x16 ){
        log->warning("Header is error number: " + QStringLiteral("%1 %2 %3").arg(nc[0])
                .arg(nc[1])
                .arg(nc[2]));
        return false;
    }

    quint8 result = 0;
    for( int i=0; i<length-1 ; i++){
        result += nc[i];
    }

    quint8 end = nc[length-1];

    if( result == end)
    {
        return true;
    }
    else{
        log->warning("check result is not same!!");
        log->warning(QStringLiteral("Sum is: %1. end check number is: %2").arg(result)
                    .arg(end));
        return false;
    }


}

void ReceiveManager::setCommand(quint8 *nc)
{
    this->command = nc;

    emit commandChanged();
}

double ReceiveManager::getVoltage()
{
    return (double)((double)this->command[3] + ((double)this->command[4] / 100));
}

double ReceiveManager::getTemperatureInside()
{
    return (double)((double)this->command[5] + ((double)this->command[6] / 100));
}

double ReceiveManager::getTemperatureOutside()
{
    return (double)((double)this->command[7] + ((double)this->command[8] / 100));
}

double ReceiveManager::getDeep()
{
    int result = (int)(( 0 | (this->command[9] << 16)
                           | (this->command[10] << 8)
                           |  this->command[11]) );
//    qDebug() << (double)((double) result/100);
    return (double)((double) result/100);
}

double ReceiveManager::getYaw()
{
    return getAngle(this->command[12], this->command[13]);
}

double ReceiveManager::getPitch()
{
    return getAngle(this->command[14], this->command[15]);
}

double ReceiveManager::getRoll()
{
    return getAngle(this->command[16], this->command[17]);
}

double ReceiveManager::getSpeed()
{
    return (double) ((double) this->command[18] / 10 );
}

bool ReceiveManager::getDeviceStatus(int x)
{
    if( x < 1 )
        x = 1;
    if( x>8)
        x = 8;

    if( getBit(this->command[19] , 8-x) == 0 )
        return false;
    else
        return true;
}

bool ReceiveManager::isStarted()
{
    if( this->command[20] == 0x01)
        return true;
    else
        return false;
}

double ReceiveManager::getCurrent()
{
    double curH = this->command[21] ;
    double curL = this->command[22] / 100;
    return curH + curL;
}

double ReceiveManager::getPower()
{
    return getCurrent() * getVoltage();
}
