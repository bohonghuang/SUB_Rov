#include "socketmanager.h"
#include <QNetworkDatagram>

SocketManager::SocketManager(QObject *parent) : QObject(parent)
{
    this->socket = new QUdpSocket(this);
    this->timer = new QTimer();
    this->timer_time = 0;

    memset( this->data, 0, 26);
    memset( this->send_data, 0, 26);
    this->data[0] = 0xaa;
    this->data[1] = 0x55;
    this->data[2] = 0x10;

    this->send_data[0] = 0xaa;
    this->send_data[1] = 0x55;
    this->send_data[2] = 0x0c;
    connect(this->socket, &QUdpSocket::readyRead, this, &SocketManager::received);
    connect(this->timer, &QTimer::timeout, this, &SocketManager::send);
}

int SocketManager::received()
{
    int flag = 0;
    QByteArray recvdata;
    QHostAddress address;
    quint16 port ;
    recvdata.resize( socket->pendingDatagramSize() );
    socket->readDatagram(recvdata.data(), recvdata.size(), &address, &port);

    qDebug() << recvdata;
    if(canRevd == false)
        return 0;

    for( int i=0; i<recvdata.size() && i<26; i++ ){
        if( flag == 3){
            this->data[i] = recvdata.data()[i];
        }
        if( flag == 2 && (quint8) recvdata[i] == 0x10 ){
            flag = 3;
        }
        if (flag == 1 && (quint8) recvdata[i] == 0x55 ){
            flag = 2;
        }
        if( flag == 0 && (quint8) recvdata[i] == 0xaa ){
            flag = 1;
        }
    }

    emit dataChanged();


    return 1;
}

int SocketManager::send()
{
    QByteArray datagarm(26, Qt::Uninitialized);
    for( int i=0; i<26; i++ ){
        datagarm[i] = this->send_data[i];
    }
    this->socket->writeDatagram(datagarm, QHostAddress(this->_uri), this->_port);
//    this->socket->write(datagarm);
    return 1;
}

int SocketManager::startTimer()
{
    if(this->timer_time!=0)
        this->timer->start(this->timer_time);

    return 1;
}

int SocketManager::connectServer()
{
    this->socket->bind(this->_port);

//    this->socket->connectToHost(this->_uri, this->_port);
    this->canRevd = true;
    this->canSend = true;
    return 1;
}

int SocketManager::disconnectServer()
{
    this->canRevd = false;
    this->canSend = false;
    return 1;
}

int SocketManager::getData(Recv_Type rt)
{
    int  res = 0;
    switch (rt) {
    case DEEP_LOCK:  res = data[3]; break;
    case DIRECTION_LOCK: res = data[4]; break;
    case FORWORD_BACK: res = data[5]; break;
    case LEFT_RIGHT: res = data[6]; break;
    case UP_DOWN: res = data[7]; break;
    case SPIN: res = data[8]; break;
    case OIL: res = data[9]; break;
    case LIGHT: res = data[10]; break;
    case CAMERA: res = data[11]; break;
    case CLOUD: res = data[12]; break;
    case MULTIP: res = data[13]; break;
    case PI: res = data[14]; break;
    case SOUP: res = data[15]; break;
    default:
        break;

    }
    return res;
}

int SocketManager::setSendData(Send_Type st, double value)
{
    switch (st) {
    case VOLTAGE:
        this->send_data[3] = (int) value;
        this->send_data[4] = ( value - (int)value ) * 100 ;
        break;
    case INSIDE_TEMPERATURE:
        this->send_data[5] = (int) value;
        this->send_data[6] = ( value - (int)value ) * 100 ;
        break;
    case OUTSIDE_TEMPERATURE:
        this->send_data[7] = (int) value;
        this->send_data[8] = ( value - (int)value ) * 100 ;
        break;
    case DEEP:
        this->send_data[9] = ((int) value) >> 16 ;
        this->send_data[10] = ((int) value) >> 8 ;
        this->send_data[11] = ((quint8) value);
        break;
    case YAW:
        this->send_data[12] = (quint8) (((int) (value / 180 * 32768)) >> 8);
        this->send_data[13] = (quint8) ((int) (value / 180 * 32768)) ;
        break;
    case PITCH:
        this->send_data[14] = (quint8) (((int) (value / 180 * 32768)) >> 8);
        this->send_data[15] = (quint8) ((int) (value / 180 * 32768)) ;
        break;
    case ROLL:
        this->send_data[16] = (quint8) (((int) (value / 180 * 32768)) >> 8);
        this->send_data[17] = (quint8) ((int) (value / 180 * 32768)) ;
        break;
    case SPEED:
        this->send_data[18] = (int) value;
        break;

    case STATE:
        this->send_data[19] = (int) value;
        break;
    default:
        break;
    }

    return 1;
}
