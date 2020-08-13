#include "KeyManager.h"

#include "../RovApplication.h"
#include "../RovController.h"
#include <SocketManager.h>
#include <SendManager.h>


///
/// \brief KeyManager::KeyManager   默认的构造，注册本体为qml类别
///
KeyManager::KeyManager(){
    log.info("Key Manager is creating!");

    qmlRegisterUncreatableType<KeyManager>("Rov.KeyManager",1, 0, "KeyManager", "Reference only");

}
KeyManager::~KeyManager()
{
    log.info("Key Manager is Deleting!");
}
///
/// \brief KeyManager::doThings 用于做按下动作的事情
/// \param key
///
void KeyManager::doThings(Qt::Key key)
{
    RovControlCore* rovc = rovApp()->getToolbox()->getRovControlCore();
    log.info("Do --> Key::" + QString(key) + " things");

    switch (key) {
    // WASD前后左右
    case Qt::Key_W:
        rovc->do_Forward_Back_Change(1);
        break;

    case Qt::Key_S:
        rovc->do_Forward_Back_Change(-1);
        break;

    case Qt::Key_A:
        qDebug() << "A";
        rovc->do_Left_Right_Change(-1);
        break;

    case Qt::Key_D:
        rovc->do_Left_Right_Change(1);
        break;
    // Q E 左旋右旋
    case Qt::Key_Q:
        rovc->doSpinLeft();
        break;

    case Qt::Key_E:
        rovc->doSpinRight();
        break;
    // F 使灯亮 E使灯暗 主要是为符合F键位距离食指的位置更近的设计。 松开则不动
    case Qt::Key_F:
        rovc->doTurnLightUp();
        break;

    case Qt::Key_R:
        rovc->doTurnLightDown();
        break;
    // Space 使上升 Control 使下降
    case Qt::Key_Space:
        rovc->doTurnUp();
        break;

    case Qt::Key_Control:
        rovc->doTurnDown();
        break;
    // F1 深度锁定/解锁  F2 方向锁定/解锁
    case Qt::Key_F1:
        rovc->doLockDeep();
        break;

    case Qt::Key_F2:
        rovc->doLockDirection();
        break;
    // Y 加油  H 减油
    case Qt::Key_Y:
        rovc->doAddOil();
        break;

    case Qt::Key_H:
        rovc->doSubOil();
        break;
    // I 云台向上 K 云台下降 松开则不行动
    case Qt::Key_I:
        rovc->doTurnCloudUp();
        break;

    case Qt::Key_K:
        rovc->doTurnCloudDown();
        break;
    // U 机器手开  J 机器手闭  松开恢复
    case Qt::Key_U:
        rovc->doTurnMachineOpen();
        break;

    case Qt::Key_J:
        rovc->doTurnMachineClose();
        break;

    case Qt::Key_Up:
    case Qt::Key_8:
        rovc->doCameraZoomingToLarge();
        break;

    case Qt::Key_Down:
    case Qt::Key_5:
        rovc->doCameraZoomingToSmall();
        break;

    case Qt::Key_Left:
    case Qt::Key_4:
        rovc->doCameraFocusingToSmall();
        break;

    case Qt::Key_Right:
    case Qt::Key_6:
        rovc->doCameraFocusingToLarge();
        break;

    case Qt::Key_P:
        rovc->doCamputure();
        break;
    default:
        break;
    }


    qDebug() << rovApp()->getToolbox()->getSocketManager()->getSendManager()->sendcmd.left_right;
}

///
/// \brief KeyManager::doRelease 用于做释放动作的事情
/// \param key
///
void KeyManager::doRelease(Qt::Key key)
{
    RovControlCore* rovControl = rovApp()->getToolbox()->getRovControlCore();

    log.info("Do --> Key::" + QString(key) + " Release things");

    switch( key ){
    case Qt::Key_W:
    case Qt::Key_S:
        rovControl->do_Forward_Back_Change(0);
        break;

    case Qt::Key_A:
    case Qt::Key_D:
        rovControl->do_Left_Right_Change(0);
        break;

    case Qt::Key_F:
    case Qt::Key_R:
        rovControl->doTurnLightNormal();
        break;

    case Qt::Key_Q:
    case Qt::Key_E:
        rovControl->doStopSpin();
        break;

    case Qt::Key_Space:
    case Qt::Key_Control:
        rovControl->doStopUpDown();
        break;

    case Qt::Key_Y:
    case Qt::Key_H:
        break;

    case Qt::Key_J:
    case Qt::Key_U:
        rovControl->doTurnMachineNormal();
        break;

    case Qt::Key_I:
    case Qt::Key_K:
        rovControl->doTurnCloudNormal();
        break;

    case Qt::Key_4:
    case Qt::Key_6:
    case Qt::Key_8:
    case Qt::Key_5:
    case Qt::Key_Left:
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Right:
        rovControl->doCameraNormal();
        break;
    default:
        break;
    }
}
