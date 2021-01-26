#include "socketmanager.h"
#include <QNetworkDatagram>

SocketManager::SocketManager(QObject *parent) : QObject(parent)
{
    this->socket = new QUdpSocket(this);
    this->tcpSocket = new QTcpSocket(this);
    this->timer = new QTimer();
    this->timer_time = 0;

    memset( this->data, 0, 26);
    memset( this->send_data, 0, 26);
    this->data[0] = 0xaa;
    this->data[1] = 0x55;
    this->data[2] = 0x0c;

    this->send_data[0] = 0xaa;
    this->send_data[1] = 0x55;
    this->send_data[2] = 0x10;

//    connect(this->tcpSocket, &QTcpSocket::connected, this, [=]() {
//        qDebug() << "connected";
//    });
    connect(this->tcpSocket, &QTcpSocket::readyRead, this, &SocketManager::received);
    connect(this->timer, &QTimer::timeout, this, &SocketManager::send);

//    QTimer timer;
//    connect(&timer, &QTimer::timeout, this, [=](){
//        static int cnt = 0;
//        cnt ++;
//        if( this->tcpSocket->isOpen() ){
//            cnt = 0;
//        }
//        if( cnt == 5){
//            qDebug() << "Non connected";
//            this->tcpSocket->disconnect();
//        }
//    });
//    timer.start(1000);
}

int SocketManager::received()
{
    int flag = 0;

    QByteArray recvdata;
    QHostAddress address;
    quint16 port ;
    recvdata.resize(26 /*socket->pendingDatagramSize()*/ );
//    recvdata = socket->read(recvdata.size());
    socket->readDatagram(recvdata.data(), recvdata.size(), &address, &port);

    qDebug() << recvdata;
    if(canRevd == false)
        return 0;


    for( int i=0; i<recvdata.size()&& i<26; i++ ){
        if( flag == 3){
            this->data[i] = recvdata[i];
        }
        if( flag == 2 && (quint8) recvdata[i] == 0x0c ){
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
//    this->tcpSocket->connectToHost(this->_uri, this->_port);

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

double SocketManager::getData(Recv_Type rt)
{
    double   res = 0;
    switch (rt) {
    case VOLTAGE:
        res = ( data[3] + (data[4]*1.0 / 100) );
        break;
    case INSIDE_TEMPERATURE:
        res = ( data[5] + (data[6]*1.0 / 100) );
        break;
    case OUTSIDE_TEMPERATURE:
        res = ( data[7] + (data[8]*1.0 / 100) );
        break;
    case DEEP:
        res = ( data[9] << 16 | data[10] << 8 | data[11] );
        break;
    case YAW:
        res = ( data[12] << 8 | data[13] ) * 1.0 / 32768 * 180;
        break;
    case PITCH:
        res = ( data[14] << 8 | data[15] ) * 1.0 / 32768 * 180;
        break;
    case ROLL:
        res = ( data[16] << 8 | data[17] ) * 1.0 / 32768 * 180;
        break;
    case SPEED:
        res = data[18];
        break;
    case STATE:
        res = data[19];
        break;
    default:
        break;


    }
    return res;
}

int SocketManager::setSendData(Send_Type st, int value)
{
    switch (st) {
    case DEEP_LOCK: send_data[3] = value; break;
    case DIRECTION_LOCK:send_data[4] = value; break;
    case FORWORD_BACK: send_data[5] = value; break;
    case LEFT_RIGHT: send_data[6] = value; break;
    case UP_DOWN:send_data[7] = value; break;
    case SPIN: send_data[8] = value; break;
    case OIL: send_data[9] = value; break;
    case LIGHT: send_data[10] = value; break;
    case CAMERA: send_data[11] = value; break;
    case CLOUD: send_data[12] = value; break;
    case MULTIP: send_data[13] = value; break;
    case PI: send_data[14] = value; break;
    case SOUP: send_data[15] = value; break;
    default:
        break;

    }

    return 1;
}
