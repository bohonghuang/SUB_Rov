#ifndef RECIVEMANAGER_H
#define RECIVEMANAGER_H

#include <QObject>
#include "ReceiveCommand.h"

class ReceiveManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ReceiveCommand receive NOTIFY onCommandChanged )
private:
    ReceiveCommand receive;

public:
    explicit ReceiveManager(QObject *parent = nullptr);
    //校验
    bool isTrueCommand(quint8 *);
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

    bool getRovStatus();
    int getRovDeviceStatus();
};

#endif // RECIVEMANAGER_H
