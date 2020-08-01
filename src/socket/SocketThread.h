#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>



class SocketThread : public QThread
{
public:
    SocketThread(QTcpSocket* tcp);

    void run();

    ///
    /// \brief connectServer
    /// 连接到ip
    void connectServer();
    void connectServer(QString uri, quint16 port);
    void disconnectServer();

    void EnableConnect(bool enable){this->enableConnected = enable; };
    void EnableSocket(bool enable){this->enableSocket = enable;};
    bool isEnableSocket() { return this->enableSocket; }

    int checkHead(QByteArray data);
    bool datacpy(QByteArray data, int sindex, quint8* newdata, int length = 26);

private:

    QTcpSocket * tcpSocket;
    QTimer * timerSend;
    QTimer * timerReceive;
    //启用连接
    bool enableConnected;
    //启用套接字
    bool enableSocket;
};

#endif // SOCKETTHREAD_H
