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
#include "RovBase.h"
#include "RovApplication.h"
#include "RovToolBox.h"

class SocketManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isAccept NOTIFY onAccepteChanged)
    Q_PROPERTY(ReceiveManager* receivemanager READ getReceiveManager )


public:
    SocketManager();
    ~SocketManager();


    bool isAccept;

    QString uri;
    QString port;

    QUdpSocket *uSocket;
    QTcpSocket *tSocket;

    SendManager *sendmanager;
    ReceiveManager *receivemanager;
public:
    void InitSocket();
    void ReadError(QAbstractSocket::SocketError);

    Q_INVOKABLE SendManager* getSendManager() ;
    Q_INVOKABLE ReceiveManager* getReceiveManager(){return this->receivemanager;}

    Q_INVOKABLE void disConnectServer();
    Q_INVOKABLE void connectServer();
    Q_INVOKABLE bool send();
    Q_INVOKABLE bool receive();

    QString getStringByQByteArray(QByteArray qb);
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

signals:
    Q_INVOKABLE void onUriChanged();
    Q_INVOKABLE void onPortChanged();
    void onAccepteChanged();
};

#endif // SOCKETMANAGER_H
