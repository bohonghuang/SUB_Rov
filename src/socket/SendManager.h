#ifndef SENDMANAGER_H
#define SENDMANAGER_H

#include <QObject>
#include "../Log/MyLogging.h"

class SendLogging;


class SendManager : public QObject
{
    Q_OBJECT
private:
    quint8* command;
    int maxLength;
    void initCommand();

    SendLogging* log;

public:
    explicit SendManager(QObject *parent = nullptr);

    quint8* getCommand();
    int getCommandLength();

    bool isDeepLocked();
    bool isDirectLocked();

    ///
    /// \brief Deep: 用于锁定、解锁深度控制
    /// \param v：0为默认，仅在程序初始化时出现，1：锁定，2：解锁
    ///
    void Deep(int v = 0);
    ///
    /// \brief Direction: 用于锁定、解锁方向控制
    /// \param v：0为默认，仅在程序初始化时出现，1：锁定，2：解锁
    ///
    void Direction(int v = 0);
    ///
    /// \brief ForwordBack: 用于输入并设置控制前后状态。
    /// \param v：0~255（0x00~0xFF)，默认值为128（0x80）
    ///
    void ForwordBack(quint8 v = 0x80);
    ///
    /// \brief LeftRight: 用于输入并设置控制左右状态。
    /// \param v：0~255（0x00~0xFF)，默认值为128（0x80）
    ///
    void LeftRight(quint8 v = 0x80);
    ///
    /// \brief UpDown: 用于控制上下的状态
    /// \param v：0为默认，表示不动。<=-1 ：下降，>=1：上升
    ///
    void UpDown(int v = 0);
    ///
    /// \brief Spin: 用于控制水平左右（旋转）的状态
    /// \param v：0为默认，表示不动。<=-1 ：下降，>=1：上升
    ///
    void Spin(int v = 0);
    ///
    /// \brief Oil: 用于油门的控制
    /// \param v：0为默认表示不改变，<=-1 ：下降25，>=1：上升25
    ///
    void Oil(int v = 0);
    ///
    /// \brief Light: 用于灯光的控制
    /// \param v：0为默认，表示不改变，<=-1 ：下降亮度，>=1：上升亮度
    ///
    void Light(int v = 0);
    ///
    /// \brief Cloud: 用于云台的控制
    /// \param v：0为默认，表示不改变，<=-1 ：下降角度，>=1：上升角度
    ///
    void Cloud(int v = 0);
    ///
    /// \brief Camera: 用于控制摄像头
    /// \param v：0x00为默认，表示不发生改变，0x01（大）、0x02（小）是聚焦控制，0x11、0x12是变焦控制
    ///
    void Camera(quint8 v = 0x00);
    ///
    /// \brief Manipulator: 用于控制机器手的开闭
    /// \param v：0为默认，表示不改变，<=-1 ：收紧，>=1：松开
    ///
    void Manipulator(int v = 0);
    ///
    /// \brief DeviceSwitch: 用于控制设备的开闭
    /// \param v：0为默认，表示不改变，<=-1 ：关闭，>=1：启动
    ///
    void DeviceSwitch(int v = 0);



signals:
    void deepChanged();
    void directChanged();
    void commandChanged();
};

class SendLogging : public MyLogging
{
public:
    void info(const QString& msg ){ log(msg, INFO, SEND_LOGGING); }
    void debug(const QString& msg ){ log(msg, DEBUG, SEND_LOGGING); }
    void warning(const QString& msg ){ log(msg, WARNING, SEND_LOGGING); }
};

#endif // SENDMANAGER_H
