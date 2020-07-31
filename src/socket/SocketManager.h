#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

#include <QObject>
#include "SendManager.h"
#include "ReceiveManager.h"
#include <QUdpSocket>
#include <QUrl>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include "RovApplication.h"
#include "RovToolBox.h"
#include <SocketThread.h>
#include <SettingManager.h>

class SocketManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool accept READ isEnable WRITE enableSocket NOTIFY enableChanged)


public:
    SocketManager();
    ~SocketManager();


    //bool accept;

    QString uri;
    QString port;

    QUdpSocket *uSocket;
    QTcpSocket *tSocket;

    SocketThread* myThread;

    SendManager *sendmanager;
    ReceiveManager *receivemanager;

    QString getStringByQByteArray(QByteArray qb);
    void ReadError(QAbstractSocket::SocketError);
signals:
    void enableChanged();
public slots:

    Q_INVOKABLE SendManager* getSendManager() ;
    Q_INVOKABLE ReceiveManager* getReceiveManager(){return this->receivemanager;}

    Q_INVOKABLE void disConnectServer();
    Q_INVOKABLE void connectServer();
    Q_INVOKABLE void enableSocket(bool enable);
    Q_INVOKABLE bool isEnable();

    Q_INVOKABLE void updateSettings();

    Q_INVOKABLE QString getSpeedText() ;
    //俯仰
    Q_INVOKABLE QString getPitchText() ;
    //横滚
    Q_INVOKABLE QString getYawText();
    Q_INVOKABLE QString getRollText();
    Q_INVOKABLE QString getDeepText();
    Q_INVOKABLE QString getVoltageText();
    Q_INVOKABLE QString getCurrentText();
    Q_INVOKABLE QString getPowerText();
    Q_INVOKABLE QString getTemperatureInsideText();
    Q_INVOKABLE QString getTemperatureOutsideText();
    Q_INVOKABLE bool getRovStatus();
    Q_INVOKABLE float getAngle();

};



#endif // SOCKETMANAGER_H
