#include "SocketThread.h"

SocketThread::SocketThread()
{
    this->socket = new QTcpSocket(this);

    _socketed = false;
    _connected = false;
}

void SocketThread::run(){
    //连接
    connect(socket, &QTcpSocket::connected, this, [=]{
        if( _socketed )
            _connected = true;
    });
    //断开
    connect(socket, &QTcpSocket::disconnected, this, [=]{
        this->_socketed = false;
        this->_connected = false;
        SocketLog.info("Disconnected!!");

        emit rovApp()->getToolbox()->getSocketManager()->enableChanged();
    });

    //发送
    connect(rovApp()->getToolbox()->getSocketManager()->getSendManager()
            , &SendManager::commandChanged, this, [=](){
        if(_connected){
            quint8* data = rovApp()->getToolbox()->getSocketManager()
                                   ->getSendManager()->getCommand();
            QByteArray sendData;
            sendData.resize(20);
            int length = 20;
            memcpy(sendData.data(), data, length);

            socket->write(sendData);
        }
        else{
            connectServer();
        }
    });

    //接收
    connect(socket, &QTcpSocket::readyRead, this, [=]{
        QByteArray data;
        data = socket->readAll();

        int sindex = checkHeader(data);

        quint8 memdata [26];
        bool isFlag = datacpy(data, sindex, memdata);

        SocketLog.info(QStringLiteral("1: %1, 2: %2, 3: %3, end_check: %4").arg(memdata[0])
                .arg(memdata[1]).arg(memdata[2]).arg(memdata[25]));


        if( isFlag ){
            rovApp()->getToolbox()
                    ->getSocketManager()
                    ->getReceiveManager()
                    ->setCommand(memdata);
        }
        else{
            qDebug() << "Data is error!!";
        }
    });

    exec();
}

void SocketThread::connectServer()
{
    if( _connected )
        return ;

    QString uri = rovApp()->getToolbox()->getSettingsManager()->getServerUri();
    quint16 port = rovApp()->getToolbox()->getSettingsManager()->getServerPort().toUInt();
    connectServer(uri, port);
}

void SocketThread::connectServer(QString u, quint16 p){
    socket->abort();
    socket->connectToHost(u, p);
    SocketLog.info("Connecting to " + u + " - " +p);
}

void SocketThread::disconnectServer()
{
    socket->disconnectFromHost();
    SocketLog.info("Disconnecting from host");

    this->_socketed = false;
}

int SocketThread::checkHeader(QByteArray data)
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
       SocketLog.warning("read data error!!");
       return false;
    }
    else{
        for( int i=sindex; i<sindex+length && i<size ; i++,mi++){
            newdata[mi] = data[i];
        }

        return true;
    }
}
