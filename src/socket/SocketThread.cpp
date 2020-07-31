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
    timer.start(100);


    connect(tcpSocket, &QTcpSocket::readyRead, this, [=](){
        QByteArray data;
        data = tcpSocket->readAll();

        int flag = memcmp(data.data(), data.data(), 26);


        if(! data.isEmpty() ){
            rovApp()->getToolbox()
                    ->getSocketManager()
                    ->getReceiveManager()
                    ->updateCommand(data);
            //qDebug() << data.data();
        }
        else{
            qDebug() << "Data is null";
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

    emit rovApp()->getToolbox()->getSocketManager()->enableChanged();

}
