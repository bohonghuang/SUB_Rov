#include "SocketManager.h"
#include <QDebug>
#include <SettingManager.h>

SocketManager::SocketManager(){
    qDebug("SocketManager: Create a new and first SocketManager");


    sendmanager = new SendManager();
    receivemanager = new ReceiveManager();

    myThread = new SocketThread(tSocket);
    myThread->start();


    qDebug("SocketManager: create complete");
}
SocketManager::~SocketManager(){

}

void SocketManager::updateSettings()
{
    this->uri = rovApp()->getToolbox()->getSettingManager()->getServerUri();
    this->port = rovApp()->getToolbox()->getSettingManager()->getServerPort();
}

void SocketManager::disConnectServer()
{
    myThread->disconnectServer();
}

void SocketManager::connectServer(){
    myThread->connectServer();
}

void SocketManager::enableSocket(bool enable)
{
    myThread->EnableSocket(enable);

    emit enableChanged();
}

bool SocketManager::isEnable()
{
    return myThread->isEnableSocket();
}

void SocketManager::ReadError(QAbstractSocket::SocketError)
{
    qDebug() << "SocketManager::ReadError";
}



QString SocketManager::getStringByQByteArray(QByteArray qb)
{
    int t;
    QString str = "";
    int length = qb.size();
    for( int i=0; i< length; i++){
        t = qb[i];
        str = str + t + "_";
    }

    return str;
}


SendManager* SocketManager::getSendManager()
{
    return this->sendmanager;
}


QString SocketManager::getSpeedText()
{
    float tp =  receivemanager->getSpeed();
    QString tmp = QString::number(tp, 'f', 2);

    return QStringLiteral("%1 dm/s").arg(tmp);
}

QString SocketManager::getPitchText()
{
    double tp =  receivemanager->getPitch();
    QString tmp = QString::number(tp, 'f', 2);

    return QStringLiteral("%1 °").arg(tmp);
}

QString SocketManager::getYawText()
{
    double tp =  receivemanager->getYaw();
    QString tmp = QString::number(tp, 'f', 2);

    return QStringLiteral("%1 °").arg(tmp);
}

QString SocketManager::getRollText()
{
    double t = receivemanager->getRoll();
    QString tmp = QString::number(t, 'f', 2);

    return QStringLiteral("%1 °").arg(tmp);
}

QString SocketManager::getDeepText()
{
    int t = receivemanager->getDeep();
    QString tmp = QString(t) + QStringLiteral(" 米");
    return QStringLiteral("%1 cm").arg(t);
}

QString SocketManager::getVoltageText()
{
    double t = receivemanager->getVoltage();
    QString tmp = QString::number(t, 'f', 2);

    return QStringLiteral("%1 V").arg(tmp);
}

QString SocketManager::getCurrentText()
{
    double t = receivemanager->getCurrent();
    QString tmp = QString::number(t, 'f', 2);

    return QStringLiteral("%1 A").arg(tmp);
}

QString SocketManager::getPowerText()
{
    double t = receivemanager->getPower();
    QString tmp = QString::number(t, 'f', 2);

    return QStringLiteral("%1 W").arg(tmp);
}

QString SocketManager::getTemperatureInsideText()
{
    double t = receivemanager->getTemperatureInside();
    QString tmp = QString::number(t, 'f', 2);

    return QStringLiteral("%1 ℃").arg(tmp);
}

QString SocketManager::getTemperatureOutsideText()
{
    double t = receivemanager->getTemperatureOutside();
    QString tmp = QString::number(t, 'f', 2);

    return QStringLiteral("%1 ℃").arg(tmp);
}

bool SocketManager::getRovStatus()
{
    return receivemanager->getRovStatus();
}

float SocketManager::getAngle()
{
    return receivemanager->getYaw();
}




