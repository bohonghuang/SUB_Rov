#ifndef SENDMANAGER_H
#define SENDMANAGER_H

#include <QObject>
#include "../Log/MyLogging.h"

class SendLogging : public MyLogging
{
public:
    void info(const QString& msg ){ log(msg, INFO, SEND_LOGGING); }
    void debug(const QString& msg ){ log(msg, DEBUG, SEND_LOGGING); }
    void warning(const QString& msg ){ log(msg, WARNING, SEND_LOGGING); }
};


class SendManager : public QObject
{
    Q_OBJECT
private:
    quint8* command;
    int maxLength;
    void initCommand();

public:
    explicit SendManager(QObject *parent = nullptr);

    quint8* getCommand();

    void Deep(int v = 0);
    void Direction(int v = 0);
    void ForwordBack(quint8 v = 0x80);
    void LeftRight(quint8 v = 0x80);
    void UpDown(int v = 0);
    void Spin(int v = 0);
    void Oil(int v = 0);
    void Light(int v = 0);
    void Cloud(int v = 0);
    void Camera(quint8 v = 0x00);
    void Manipulator(int v = 0);
    void DeviceSwitch(int v = 0);



signals:
    void deepChanged();
    void directChanged();
    void commandChanged();
};

#endif // SENDMANAGER_H
