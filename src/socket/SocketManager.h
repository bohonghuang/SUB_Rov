#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

#include <QThread>
#include <QTcpSocket>

#include "SocketThread.h"
#include "SendManager.h"
#include "ReceiveManager.h"


class SocketLogging;


class SocketManager : public QObject
{
    Q_OBJECT

private:
    QTcpSocket* tcpSocket;
    SocketThread* myThread;

    SendManager* sendManager;
    ReceiveManager* receiveManager;

    SocketLogging* log;

public:
    SocketManager();

    SocketThread* getThread(){return this->myThread;}
    SendManager* getSendManager(){return this->sendManager; };
    ReceiveManager* getReceiveManager(){return this->receiveManager;};

    void enableSocket(bool enable);

    typedef enum{
        SPEED,
        PITCH,
        YAW,
        ROLL,
        CURRENT,
        VOLTAGE,
        POWER,
        TEMPERATURE_INSIDE,
        TEMPERATURE_OUTSIDE,
        DEEP
    } INFO_TYPE;



public slots:
    QString getInfoText(INFO_TYPE t);
    void disconnectServer();
    void connectServer();

    bool isDeepLocked(){return this->sendManager->isDeepLocked(); }
    bool isDirectionLocked(){return this->sendManager->isDirectLocked(); }

    bool isEnable();
signals:
    void enableChanged();
    void receiveChanged();
    void sendChanged();

};

class SocketLogging : public MyLogging
{
public:
    void info(const QString& msg ){ log(msg, INFO, SOCKET_LOGGING); }
    void debug(const QString& msg ){ log(msg, DEBUG, SOCKET_LOGGING); }
    void warning(const QString& msg ){ log(msg, WARNING, SOCKET_LOGGING); }
};


#endif // SOCKETMANAGER_H
