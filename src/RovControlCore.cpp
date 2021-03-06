#include "RovControlCore.h"
#include "RovApplication.h"
#include "joystick/joystickmanager.h"
//#include "RovToolbox.h"

RovControlCore::RovControlCore(QObject *parent) : QObject(parent)
{

}

int RovControlCore::doThings(SETTING_JOY_DO sdj, bool pressed)
{
    switch(sdj) {
    case ADD_OIL:
        if(pressed) addOil();
        break;
    case SUB_OIL:
        if(pressed) subOil();
        break;
    case UP_CLOUD:
        if(pressed) upCloud();
        else normalCloud();
        break;
    case DOWN_CLOUD:
        if(pressed) downCloud();
        else normalCloud();
        break;
    case ENLARGE_FOCUSING:
        if(pressed) enlargeFocus();
        else normalCamera();
        break;
    case REDUCE_FOCUSING:
        if(pressed) reduceFocus();
        else normalCamera();
        break;
    case ENLARGE_LIGHT:
        if(pressed) upLight();
        else normalLight();
        break;
    case REDUCE_LIGHT:
        if(pressed) downLight();
        else normalLight();
        break;
    case ENLARGE_ZOOMING:
        if(pressed) enlargeZoom();
        else normalCamera();
        break;
    case REDUCE_ZOOMING:
        if(pressed) reduceZoom();
        else normalCamera();
        break;
    case LOCK_DEEP:
        if(pressed) lockDeep();
        break;
    case LOCK_DIRECTION:
        if(pressed) lockDirection();
        break;
    default:
        break;
    }

//    qDebug() << sdj;

    return 1;
}

QString RovControlCore::getInfoText(int index)
{
    QString strText = "";
    switch (index + 1) {
    case 1:
        strText = QStringLiteral("内温：%1")
                .arg(rovApp()->getToolbox()
                     ->getSocketManager()
                     ->getInfoText(SocketManager::TEMPERATURE_INSIDE));
        break;
    case 2: strText = QStringLiteral("外温：%1")
                .arg(rovApp()->getToolbox()
                     ->getSocketManager()
                     ->getInfoText(SocketManager::TEMPERATURE_OUTSIDE));
        break;
    case 3: strText = QStringLiteral("电压：%1")
                .arg(rovApp()->getToolbox()
                     ->getSocketManager()
                     ->getInfoText(SocketManager::VOLTAGE));
        break;
    case 4: strText = QStringLiteral("电流：%1")
                .arg(rovApp()->getToolbox()
                     ->getSocketManager()
                     ->getInfoText(SocketManager::CURRENT));
        break;
    case 5: strText = QStringLiteral("功率：%1")
                .arg(rovApp()->getToolbox()
                     ->getSocketManager()
                     ->getInfoText(SocketManager::POWER));
        break;
    case 6: strText = QStringLiteral("俯仰：%1")
                .arg(rovApp()->getToolbox()
                     ->getSocketManager()
                     ->getInfoText(SocketManager::PITCH));
        break;
    case 7: strText = QStringLiteral("横滚：%1")
                .arg(rovApp()->getToolbox()
                     ->getSocketManager()
                     ->getInfoText(SocketManager::ROLL));
        break;
    case 8: strText = QStringLiteral("航向：%1")
                .arg(rovApp()->getToolbox()
                     ->getSocketManager()
                     ->getInfoText(SocketManager::YAW));
        break;
    case 9: strText = QStringLiteral("速度：%1")
                .arg(rovApp()->getToolbox()
                     ->getSocketManager()
                     ->getInfoText(SocketManager::SPEED));
        break;
    case 10: strText = QStringLiteral("深度：%1")
                .arg(rovApp()->getToolbox()
                     ->getSocketManager()
                     ->getInfoText(SocketManager::DEEP));
        break;
    }
    return strText;
}

QString RovControlCore::getFlagPath(int index)
{
    QString strPath ="";

    switch (index+1) {
    case 1: strPath = QStringLiteral("qrc:/res/icon/flag/white_deep.png"); break;
    case 2: strPath = QStringLiteral("qrc:/res/icon/flag/white_com.png"); break;
    case 3: strPath = QStringLiteral("qrc:/res/icon/flag/white_eletric.png"); break;
    case 4: strPath = QStringLiteral("qrc:/res/icon/flag/white_point.png"); break;
    case 5: strPath = QStringLiteral("qrc:/res/icon/flag/white_change.png"); break;
    case 6: strPath = QStringLiteral("qrc:/res/icon/flag/white_order.png"); break;
    case 7: strPath = QStringLiteral("qrc:/res/icon/flag/white_cloud.png"); break;
    case 8: strPath = QStringLiteral("qrc:/res/icon/flag/white_machine.png"); break;
    case 9: strPath = QStringLiteral("qrc:/res/icon/flag/white_p.png"); break;
    }
    return strPath;
}

bool RovControlCore::getFlagShow(int index)
{
    if( index < 8 )
        return rovApp()->getToolbox()
                ->getSocketManager()
                ->getReceiveManager()
                ->getDeviceStatus(index + 1);
    else
        return !rovApp()->getToolbox()->getSocketManager()
                ->getReceiveManager()->isStarted();
}

double RovControlCore::getPointerAngle()
{
    return rovApp()->getToolbox()->getSocketManager()->getReceiveManager()->getYaw();
}

int RovControlCore::getRovStateX(int i)
{
    return getRovState(i).x;
}

int RovControlCore::getRovStateY(int i)
{
    return getRovState(i).y;
}

QString RovControlCore::getRovStateSource(int i)
{
    return getRovState(i).source;
}

QString RovControlCore::getRovStateLightSource(int i)
{
    rov_body_Image_show_info info;
    switch (i) {
    case 1 :
        // 左旋暗
        info.x = 94;
        info.y = 1;
        info.source = "qrc:/res/icon/rov/left_spin_light.png";
        break;
    case 2 :
        // 右旋暗
        info.x =133;
        info.y = 1;
        info.source = "qrc:/res/icon/rov/right_spin_light.png";
        break;
    case 3 :
        // 俯视角机身
        info.x = 106;
        info.y = 12;
        info.source = "qrc:/res/icon/rov/body1.png";
        break;

    case 4 :
        // 主视角机身
        info.x = 27;
        info.y = 1;
        info.source = "qrc:/res/icon/rov/body2.png";
        break;
    case 5 :
        // 上暗
        info.x = 44;
        info.y = 1;
        info.source = "qrc:/res/icon/rov/up_light.png";

        break;
    case 6 :
        // 左暗
        info.x = 13;
        info.y = 39;
        info.source = "qrc:/res/icon/rov/left_light.png";
        break;
    case 7 :
        // 右暗
        info.x = 65;
        info.y = 0;
        info.source = "qrc:/res/icon/rov/right_light.png";
        break;
    case 8 :
        // 下暗
        info.x = 44;
        info.y = 42;
        info.source = "qrc:/res/icon/rov/down_light.png";
        break;
    case 9 :
        info.x = 4;
        info.y = 22;
        info.source = "qrc:/res/icon/rov/forward_light.png";
        break;
    case 10 :
        // 后暗
        info.x = 68;
        info.y = 22;
        info.source = "qrc:/res/icon/rov/back_light.png";
        break;
        break;
    }


    return info.source;
}

rov_body_Image_show_info RovControlCore::getRovState(int i)
{
    rov_body_Image_show_info info;
    switch (i) {
    case 1 :
        // 左旋暗
        info.x = 94;
        info.y = 1;
        info.source = "qrc:/res/icon/rov/left_spin_dark.png";
        break;
    case 2 :
        // 右旋暗
        info.x =133;
        info.y = 1;
        info.source = "qrc:/res/icon/rov/right_spin_dark.png";
        break;
    case 3 :
        // 俯视角机身
        info.x = 106;
        info.y = 12;
        info.source = "qrc:/res/icon/rov/body2.png";
        break;

    case 4 :
        // 主视角机身
        info.x = 27;
        info.y = 12;
        info.source = "qrc:/res/icon/rov/body1.png";
        break;
    case 5 :
        // 上暗
        info.x = 44;
        info.y = 1;
        info.source = "qrc:/res/icon/rov/up_dark.png";

        break;
    case 6 :
        // 左暗
        info.x = 13;
        info.y = 39;
        info.source = "qrc:/res/icon/rov/left_dark.png";
        break;
    case 7 :
        // 右暗
        info.x = 65;
        info.y = 0;
        info.source = "qrc:/res/icon/rov/right_dark.png";
        break;
    case 8 :
        // 下暗
        info.x = 44;
        info.y = 42;
        info.source = "qrc:/res/icon/rov/down_dark.png";
        break;
    case 9 :
        info.x = 4;
        info.y = 22;
        info.source = "qrc:/res/icon/rov/forward_dark.png";
        break;
    case 10 :
        // 后暗
        info.x = 68;
        info.y = 22;
        info.source = "qrc:/res/icon/rov/back_dark.png";
        break;
        break;
    }


    return info;
}

void RovControlCore::up()
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->UpDown(1);
}

void RovControlCore::down()
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->UpDown(-1);
}

void RovControlCore::stopUpDown()
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->UpDown(0);
}

void RovControlCore::updown(int value)
{

    rovApp()->getToolbox()->getSocketManager()->getSendManager()->UpDown(value);

    if(value > 200)
        emit onDown();
    else if(value < 50 )
        emit onUp();
    else emit onUDN();
}

void RovControlCore::spin(int value)
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->Spin(value);


    if(value > 200)
        emit onRSpin();
    else if(value < 50 )
        emit onLSpin();
    else emit onSN();
}

void RovControlCore::forwardBack(double axist)
{
    quint8 t = axist * 127 + 127 + 1;
    forwardBack(t);


}

void RovControlCore::forwardBack(int value)
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->ForwordBack(value);


    if(value > 200)
        emit onBack();
    else if(value < 50 )
        emit onForward();
    else emit onFBN();

}

void RovControlCore::leftRight(int value) {
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->LeftRight((quint8)value);

    if(value > 200)
        emit onRight();
    else if(value < 50 )
        emit onLeft();
    else emit onLRN();
}
void RovControlCore::leftRight(double axist)
{
    quint8 t = axist * 127 + 127 + 1;
    leftRight(t);
}

void RovControlCore::spinLeft()
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->Spin(-1);
}

void RovControlCore::spinRight()
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->Spin(1);
}

void RovControlCore::stopSpin()
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->Spin(0);
}

///
/// \brief RovControlCore::lockDeep
///  能解锁和开锁
void RovControlCore::lockDeep()
{
    if( rovApp()->getToolbox()->getSocketManager()->getSendManager()->isDeepLocked() )
        unlockDeep();
    else
        rovApp()->getToolbox()->getSocketManager()->getSendManager()->Deep(1);
}

///
/// \brief RovControlCore::unlockDeep
///
void RovControlCore::unlockDeep()
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->Deep(2);
}

///
/// \brief RovControlCore::lockDirection
/// 能解锁和开锁
void RovControlCore::lockDirection()
{
    if( rovApp()->getToolbox()->getSocketManager()->getSendManager()->isDirectLocked() )
        unlockDirection();
    else
        rovApp()->getToolbox()->getSocketManager()->getSendManager()->Direction(1);
}

void RovControlCore::unlockDirection()
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->Direction(2);
}

void RovControlCore::grabImage()
{
    rovApp()->getToolbox()->getVideoManager()->grabImage();
}

void RovControlCore::enlargeZoom()
{
    quint8 t = 0x11;
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->Camera(t);
}

void RovControlCore::reduceZoom()
{
    quint8 t = 0x12;
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->Camera(t);
}

void RovControlCore::enlargeFocus()
{
    quint8 t = 0x01;
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->Camera(t);
}

void RovControlCore::reduceFocus()
{
    quint8 t = 0x02;
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->Camera(t);
}

void RovControlCore::normalCamera()
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->Camera();
}

void RovControlCore::addOil()
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->Oil(1);
}

void RovControlCore::subOil()
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->Oil(-1);
}

void RovControlCore::upCloud()
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->Cloud(1);
}

void RovControlCore::downCloud()
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->Cloud(-1);
}

void RovControlCore::normalCloud()
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->Cloud();
}

void RovControlCore::upLight()
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->Light(1);
}

void RovControlCore::downLight()
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->Light(-1);
}

void RovControlCore::normalLight()
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->Light();
}

void RovControlCore::openManipulator()
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->Manipulator(1);
}

void RovControlCore::closeManipulator()
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->Manipulator(-1);
}

void RovControlCore::normalManipulator()
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->Manipulator();
}

void RovControlCore::startDevice()
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->DeviceSwitch(1);
}

void RovControlCore::stopDevice()
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->DeviceSwitch(-1);
}

void RovControlCore::normalDevice()
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->DeviceSwitch(0);
}

void RovControlCore::turnDeivce()
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->TurnDevice();
}

void RovControlCore::startPi()
{

}

void RovControlCore::stopPi()
{

}

void RovControlCore::startRecording()
{
    rovApp()->getToolbox()->getVideoManager()->startRecord();
}

void RovControlCore::stopRecording()
{
    rovApp()->getToolbox()->getVideoManager()->stopRecord();
}
