#include "KeyManager.h"

#include "../RovApplication.h"
#include "../RovControlCore.h"
#include "../RovToolbox.h"
#include "../Socket/SocketManager.h"
#include "../Socket/SendManager.h"


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
//    log.info("Do --> Key::" + QString(key) + " things");
//    qDebug()<<"Do --> Key::" + QString(key) + " things";
    switch (key) {
    // WASD前后左右
    case Qt::Key_W:
        rovc->forwardBack(1);
        break;

    case Qt::Key_S:
        rovc->forwardBack(-1);
        break;

    case Qt::Key_A:
        rovc->leftRight(-1);
        break;

    case Qt::Key_D:
        rovc->leftRight(1);
        break;
    // Q E 左旋右旋
    case Qt::Key_Q:
        rovc->spinLeft();
        break;

    case Qt::Key_E:
        rovc->spinRight();
        break;
    // F 使灯亮 E使灯暗 主要是为符合F键位距离食指的位置更近的设计。 松开则不动
    case Qt::Key_F:
        rovc->upLight();
        break;

    case Qt::Key_R:
        rovc->downLight();
        break;
    // Space 使上升 Control 使下降
    case Qt::Key_Space:
        rovc->up();
        break;

    case Qt::Key_Control:
        rovc->down();
        break;
    // F1 深度锁定/解锁  F2 方向锁定/解锁
    case Qt::Key_F1:
        rovc->lockDeep();
        break;

    case Qt::Key_F2:
        rovc->lockDirection();
        break;
    // Y 加油  H 减油
    case Qt::Key_Y:
        rovc->addOil();
        break;

    case Qt::Key_H:
        rovc->subOil();
        break;
    // I 云台向上 K 云台下降 松开则不行动
    case Qt::Key_I:
        rovc->upCloud();
        break;

    case Qt::Key_K:
        rovc->downCloud();
        break;
    // U 机器手开  J 机器手闭  松开恢复
    case Qt::Key_U:
        rovc->openManipulator();
        break;

    case Qt::Key_J:
        rovc->closeManipulator();
        break;

    case Qt::Key_Up:
    case Qt::Key_8:
        rovc->enlargeZoom();
        break;

    case Qt::Key_Down:
    case Qt::Key_5:
        rovc->reduceZoom();
        break;

    case Qt::Key_Left:
    case Qt::Key_4:
        rovc->reduceFocus();
        break;

    case Qt::Key_Right:
    case Qt::Key_6:
        rovc->enlargeFocus();
        break;

    case Qt::Key_P:
        rovc->grabImage();
        break;
    default:
        break;
    }

}

///
/// \brief KeyManager::doRelease 用于做释放动作的事情
/// \param key
///
void KeyManager::doRelease(Qt::Key key)
{
    RovControlCore* rovControl = rovApp()->getToolbox()->getRovControlCore();

    log.info("Do --> Key::" + QStringLiteral("%1").arg( key ) + " Release things");

    switch( key ){
    case Qt::Key_W:
    case Qt::Key_S:
        rovControl->forwardBack(0);
        break;

    case Qt::Key_A:
    case Qt::Key_D:
        rovControl->leftRight(0);
        break;

    case Qt::Key_F:
    case Qt::Key_R:
        rovControl->normalLight();
        break;

    case Qt::Key_Q:
    case Qt::Key_E:
        rovControl->stopSpin();
        break;

    case Qt::Key_Space:
    case Qt::Key_Control:
        rovControl->stopUpDown();
        break;

    case Qt::Key_Y:
    case Qt::Key_H:
        break;

    case Qt::Key_J:
    case Qt::Key_U:
        rovControl->normalManipulator();
        break;

    case Qt::Key_I:
    case Qt::Key_K:
        rovControl->normalCloud();
        break;

    case Qt::Key_4:
    case Qt::Key_6:
    case Qt::Key_8:
    case Qt::Key_5:
    case Qt::Key_Left:
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Right:
        rovControl->normalCamera();
        break;
    default:
        break;
    }
}
