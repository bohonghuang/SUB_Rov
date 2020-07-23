#include "SocketManager.h"
#include <QDebug>
#include <SettingManager.h>

SocketManager::SocketManager(){
    qDebug("SocketManager: Create a new and first SocketManager");


    sendmanager = new SendManager();
    receivemanager = new ReceiveManager();
    InitSocket();
    qDebug("SocketManager: create complete");
}
SocketManager::~SocketManager(){

}

void SocketManager::updateSettings()
{
    qDebug() << "SocketManager::updateSettings() in";
    this->uri = rovApp()->getToolbox()->getSettingManager()->getServerUri();
    this->port = rovApp()->getToolbox()->getSettingManager()->getServerPort();
    qDebug() << "SocketManager::updateSettings() out";
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




///
/// \brief SocketManager::InitSocket
/// 初始化udpsocket， 并建立一个槽信号连接
void SocketManager::InitSocket(){
    qDebug("SocketManager::InitSocket() in");
    tSocket = new QTcpSocket(this);

    connect(tSocket, &QTcpSocket::readyRead, this, &SocketManager::receive);
    connect(tSocket, &QTcpSocket::connected, this, [=](){
        this->isAccept = true;
        qDebug() << "connected";
    });

    QTimer *timer = new QTimer();
    connect(timer, &QTimer::timeout, this, [=](){
        if(this->isAccept == true){
            this->receive();
            this->send();
        }
    });
    timer->start(200);

    qDebug("SocketManager::InitSocket() out");

}

void SocketManager::disConnectServer()
{
    qDebug("SocketManager::disConnectServer() in") ;
    if(tSocket!=nullptr){
        tSocket->disconnectFromHost();
        //tSocket->close();
        qDebug() << "connect is close" ;
    }
    qDebug("SocketManager::disConnectServer() in") ;
}

void SocketManager::connectServer(){
    qDebug("SocketManager::connectServer() in") ;
    updateSettings();
    tSocket->abort();
    QString uri = this->uri;
    qint16 p = port.toUInt() ;
    tSocket->connectToHost( uri , p);

    qDebug() << "connect to "<< uri << " - " << p ;
    qDebug("SocketManager::connectServer() out") ;
}

void SocketManager::ReadError(QAbstractSocket::SocketError)
{
    qDebug() << "SocketManager::ReadError";
}


///
/// \brief SocketManager::Send
/// \return
/// 向对向udp发送数据
bool SocketManager::send(){

    QByteArray senddata = sendmanager->getBytearrayCommand();

    tSocket->write(senddata);

    return true;
}


///
/// \brief SocketManager::Receive
/// \return
/// 接收来自对方的数据内容, 是否运行取决于
///  udpsocket 监听端口的情况
bool SocketManager::receive(){
    // 接收 bytearray数据 --> 转换为 tmp数据 ---> 交给 receivemanager 处理
    QByteArray data;
    QByteArray tdata;

    data = tSocket->readAll();
    memcpy(data.data(), data.data(), 26);
    if(!data.isEmpty()){
        receivemanager->updateCommand(data);
        qDebug() << "Receive the data: " + getStringByQByteArray(data);
        qDebug() << "Receive the tdata: " + getStringByQByteArray(tdata);
    }
    else
        return false;

    return true;
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
