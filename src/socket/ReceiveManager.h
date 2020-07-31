#ifndef RECIVEMANAGER_H
#define RECIVEMANAGER_H

#include <QObject>
#include <QThread>
#include "ReceiveCommand.h"

class ReceiveManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ReceiveCommand receive READ getReceive NOTIFY recvCommandChanged)
    Q_PROPERTY(quint8 deviceStatus READ getDeviceStatus NOTIFY onDeviceStatusChanged )

private:
    ReceiveCommand receive;

public:
    explicit ReceiveManager(QObject *parent = nullptr);
    ReceiveCommand getReceive() {return this->receive;}
    //校验
    bool isTrueCommand(quint8 *, int);
    bool isTrueCommand(QByteArray);
    //更新内容
    void updateCommand(quint8 *);
    void updateCommand(QByteArray data);
    //角度，可能用不到
    double GetAngle(quint8 high, quint8 low);
    //角度
    float GetCalcAngle(quint8 high, quint8 low);
    int GetBit(quint8 num, quint8 pos);

    int getDeep();
    //电压
    double getVoltage();
    //电流
    double getCurrent();
    //功率
    double getPower();
    //内舱温度
    double getTemperatureInside();
    //外水温
    double getTemperatureOutside();
    //航向角
    double getYaw();
    //横滚角
    double getRoll();
    //俯仰角
    double getPitch();
    //速度
    float getSpeed();
    //
    int getDeviceStatus();
public slots:
    bool getRovStatus();
    bool getRovDeviceStatus(int x);

signals:
    void onDeviceStatusChanged();
    void recvCommandChanged();
};

#endif // RECIVEMANAGER_H
