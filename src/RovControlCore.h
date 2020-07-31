#ifndef ROVCONTORLCORE_H
#define ROVCONTORLCORE_H

#include <QObject>
#include <VideoManager.h>

class RovControlCore : public QObject
{
    Q_OBJECT
public:
    explicit RovControlCore(QObject *parent = nullptr);

public slots:

    void doTurnUp();
    void doTurnDown();
    void doStopUpDown();


    void do_Forward_Back_Change(double axist);
    void do_Left_Right_Change(double axist);

    void doSpinLeft();
    void doSpinRight();
    void doStopSpin();

    void doLockDeep();
    void doLockDirection();
    //
    void doTurnLight();
    void doTurnLightUp();
    void doTurnLightDown();
    void doTurnLightNormal();
    //拍照
    void doCamputure();
    //紧急关闭操作
    void doKeep5();
    void doRecord();
    void doCameraFocusing(double axit);
    void doCameraZooming(double axit);
    void doCameraFocusingToLarge();
    void doCameraFocusingToSmall();
    void doCameraZoomingToLarge();
    void doCameraZoomingToSmall();
    void doCameraNormal();
    //
    void doAddOil();
    void doSubOil();
    //
    void doTurnCloud();
    void doTurnCloudUp();
    void doTurnCloudDown();
    void doTurnCloudCentral();
    void doTurnCloudNormal();
    //
    void doTurnMachineOpen();
    void doTurnMachineClose();
    void doTurnMachineNormal();
    //
    void doStart();
    void doStop();
signals:

};

#endif // ROVCONTORLCORE_H
