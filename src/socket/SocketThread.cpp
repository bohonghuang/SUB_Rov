#include "SocketThread.h"
#include <RovApplication.h>
#include <SettingManager.h>
#include <SocketManager.h>

SocketThread::SocketThread(QTcpSocket *t){
    this->tcpSocket = t;
    tcpSocket = new QTcpSocket(this);

    enableSocket = false;
    enableConnected = false;
}

void SocketThread::run()
{
    //连接到
    connect(tcpSocket, &QTcpSocket::connected, this, [=](){
        if( enableSocket ){
            this->enableConnected = true;
        }
    });
    //断开连接
    connect(tcpSocket, &QTcpSocket::disconnected, this, [=](){
        this->enableSocket = false;
        this->enableConnected = false;
        qDebug() << "Disconnected!" ;

        emit rovApp()->getToolbox()->getSocketManager()->enableChanged();
    });


    QTimer timer;
    connect(&timer, &QTimer::timeout, this, [=](){
        if( enableConnected ) {
            QByteArray senddata = rovApp()->getToolbox()
                    ->getSocketManager()->getSendManager()
                    ->getBytearrayCommand();

            tcpSocket->write(senddata);
        }
        else if( enableSocket ){
            connectServer();
        }
    });
    timer.start(500);


    connect(tcpSocket, &QTcpSocket::readyRead, this, [=](){
        QByteArray data;
        data = tcpSocket->readAll();
//        data.

        int sindex = checkHead(data);

        quint8 memdata [26];
        bool isFlag = datacpy(data, sindex, memdata);
        qDebug() << memdata[0] << " - " << memdata[1] << " - " << memdata[25];
        memcpy(data.data(), memdata, 26);


        if( isFlag ){
            rovApp()->getToolbox()
                    ->getSocketManager()
                    ->getReceiveManager()
                    ->updateCommand(data);
        }
        else{
            qDebug() << "Data is error!!";
        }
    });
    exec();
}

void SocketThread::connectServer()
{
    if( enableConnected ){
        return ;
    }
    QString uri = rovApp()->getToolbox()->getSettingManager()->getServerUri();
    qint16 port = rovApp()->getToolbox()->getSettingManager()->getServerPort().toUInt();

    connectServer(uri, port);
}

void SocketThread::connectServer(QString u, quint16 p)
{
    tcpSocket->abort();
    tcpSocket->connectToHost( u , p);

    qDebug() << "connect to "<< u << " - " << p ;
}

void SocketThread::disconnectServer()
{
    if(tcpSocket!=nullptr){
        tcpSocket->disconnectFromHost();

        qDebug() << "connect is closed" ;
    }
    this->enableSocket = false;

}

int SocketThread::checkHead(QByteArray data)
{
    int length = data.size();
    int sindex = 0;
    int cnt = 0;

    for( int i=0; i<length; i++){
        quint8 tmp = data[i];
        if(tmp == 0xaa && cnt == 0){
            cnt++;
            sindex = i;
        }
        else if(tmp == 0x55 && cnt == 1){
            cnt++;
        }
        else if( tmp == 0x16 && cnt == 2){
            break;
        }
        else{
            cnt = 0;
            sindex = 0;
        }
    }

    return sindex;
}

bool SocketThread::datacpy(QByteArray data, int sindex, quint8 *newdata, int length)
{
    int mi = 0;
    int size = data.size();

    if(size - sindex < length)
    {
           qWarning() << "read data error!!";
           return false;
    }
    else{
        for( int i=sindex; i<sindex+length && i<size ; i++,mi++){
            newdata[mi] = data[i];
        }

        return true;
    }

}
