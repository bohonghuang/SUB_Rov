#ifndef ROVCONTORLCORE_H
#define ROVCONTORLCORE_H

#include <QObject>
#include <VideoManager.h>

class RovControlCore : public QObject
{
    Q_OBJECT
public:
    explicit RovControlCore(QObject *parent = nullptr);

Q_INVOKABLE public:

    Q_INVOKABLE void doTurnUp();
    Q_INVOKABLE void doTurnDown();
    Q_INVOKABLE void doStopUpDown();


    Q_INVOKABLE void do_Forward_Back_Change(double axist);
    Q_INVOKABLE void do_Left_Right_Change(double axist);

    Q_INVOKABLE void doSpinLeft();
    Q_INVOKABLE void doSpinRight();
    Q_INVOKABLE void doStopSpin();

    Q_INVOKABLE void doLockDeep();
    Q_INVOKABLE void doLockDirection();
    //
    Q_INVOKABLE void doTurnLight();
    Q_INVOKABLE void doTurnLightUp();
    Q_INVOKABLE void doTurnLightDown();
    Q_INVOKABLE void doTurnLightNormal();
    //拍照
    Q_INVOKABLE void doCamputure();
    //紧急关闭操作
    Q_INVOKABLE void doKeep5();
    Q_INVOKABLE void doRecord();
    Q_INVOKABLE void doCameraFocusing(double axit);
    Q_INVOKABLE void doCameraZooming(double axit);
    Q_INVOKABLE void doCameraFocusingToLarge();
    Q_INVOKABLE void doCameraFocusingToSmall();
    Q_INVOKABLE void doCameraZoomingToLarge();
    Q_INVOKABLE void doCameraZoomingToSmall();
    Q_INVOKABLE void doCameraNormal();
    //
    Q_INVOKABLE void doAddOil();
    Q_INVOKABLE void doSubOil();
    //
    Q_INVOKABLE void doTurnCloud();
    Q_INVOKABLE void doTurnCloudUp();
    Q_INVOKABLE void doTurnCloudDown();
    Q_INVOKABLE void doTurnCloudCentral();
    Q_INVOKABLE void doTurnCloudNormal();
    //
    Q_INVOKABLE void doTurnMachineOpen();
    Q_INVOKABLE void doTurnMachineClose();
    Q_INVOKABLE void doTurnMachineNormal();
signals:

};

#endif // ROVCONTORLCORE_H
