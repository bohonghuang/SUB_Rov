#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QTimer>
#include <QObject>

#include "../RovApplication.h"
#include "SocketManager.h"

class SocketThread : public QThread
{
    Q_OBJECT
public:
    SocketThread();
    void run() override;
    void connectServer();
    void connectServer(QString u, quint16 p);
    void disconnectServer();

    void enableConnect(bool enable) {this->_connected = enable;}
    bool isEnableConnect() {return this->_connected; }
    void enableSocket(bool enable) {this->_socketed = enable; }
    bool isEnableSocket() {return this->_socketed;}

private:
    QTcpSocket* socket;
    bool _connected;
    bool _socketed;

    int checkHeader(QByteArray data);
    bool datacpy(QByteArray data, int sindex, quint8*newdata, int length=20);

};

#endif // SOCKETTHREAD_H
