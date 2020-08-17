#ifndef ROVCONTROLCORE_H
#define ROVCONTROLCORE_H

#include <QObject>

class RovControlCore : public QObject
{
    Q_OBJECT
public:
    explicit RovControlCore(QObject *parent = nullptr);
public slots:
    QString getInfoText(int index);
    QString getFlagPath(int index);
    bool getFlagShow(int index);
    double getPointerAngle();
    ///
    /// \brief 上升
    ///
    void up();
    void down();
    void stopUpDown();


    void forwardBack(double axist);
    void leftRight(double axist);

    void spinLeft();
    void spinRight();
    void stopSpin();

    void lockDeep();
    void unlockDeep();
    void lockDirection();
    void unlockDirection();

    ///
    /// \brief 截图/拍照
    ///
    void grabImage();

    ///
    /// \brief 变焦放大
    ///
    void enlargeZoom();
    ///
    /// \brief 变焦缩小
    ///
    void reduceZoom();
    ///
    /// \brief 聚焦放大
    ///
    void enlargeFocus();
    ///
    /// \brief 聚焦缩小
    ///
    void reduceFocus();
    void normalCamera();

    ///
    /// \brief 加油
    ///
    void addOil();
    ///
    /// \brief 减油
    ///
    void subOil();

    ///
    /// \brief 升起云台
    ///
    void upCloud();
    ///
    /// \brief 降下云台
    ///
    void downCloud();
    void normalCloud();

    void upLight();
    void downLight();
    void normalLight();
    ///
    /// \brief 打开机械手
    ///
    void openManipulator();
    ///
    /// \brief 关闭机械手
    ///
    void closeManipulator();
    ///
    /// \brief 机械手常态
    ///
    void normalManipulator();

    ///
    /// \brief 启动设备
    ///
    void startDevice();
    ///
    /// \brief 停止设备
    ///
    void stopDevice();

    ///
    /// \brief 启动pi
    ///
    void startPi();
    ///
    /// \brief 停止 pi
    ///
    void stopPi();

    ///
    /// \brief 启动录像
    ///
    void startRecording();
    ///
    /// \brief 停止录像
    ///
    void stopRecording();
signals:

};

#endif // ROVCONTROLCORE_H
