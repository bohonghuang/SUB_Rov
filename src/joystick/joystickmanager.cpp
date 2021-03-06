#include "joystickmanager.h"

#define AXIS_CENTER_LEFT 30840
#define AXIS_CENTER_RIGHT 33410

int getAxisValue(int value){
    return  value * 1.0 / 65535 * 255;
}
JoyStickManager::JoyStickManager(QObject *parent) : QObject(parent)
{
    this->joy = new JoyThread();
    qRegisterMetaType<joyinfoex_tag>("joyinfoex_tag");
    this->joy->start();
    this->typeCon = XBOX_360;

    connect(this->joy, &JoyThread::JoySignal_row, this, [=](joyinfoex_tag state){
        if(this->typeCon == XBOX_360 ){
            emit onLeftAxisXChanged( getAxisValue(state.dwXpos) );
            emit onLeftAxisYChanged( getAxisValue(state.dwYpos) );
            emit onRightAxisXChanged( getAxisValue(state.dwUpos) );
            emit onRightAxisYChanged( getAxisValue(state.dwRpos) );
            emit onLTRTChanged( getAxisValue(state.dwZpos));

            if( (state.dwButtons & 0x01 << 0) ){
                emit onButtonAChanged(true);
//                qDebug("123");
            } else {
                emit onButtonAChanged(false);
            }
            if( (state.dwButtons & 0x01 << 1) ){
                emit onButtonBChanged(true);
            } else {
                emit onButtonBChanged(false);
            }
            if( (state.dwButtons & 0x01 << 2) ){
                emit onButtonXChanged(true);
            } else {
                emit onButtonXChanged(false);
            }
            if( (state.dwButtons & 0x01 << 3) ){
                emit onButtonYChanged(true);
            } else {
                emit onButtonYChanged(false);
            }
            if( (state.dwButtons & 0x01 << 4) ){
                emit onButtonLBChanged(true);
            } else {
                emit onButtonLBChanged(false);
            }
            if( (state.dwButtons & 0x01 << 5) ){
                emit onButtonRBChanged(true);
            } else {
                emit onButtonRBChanged(false);
            }
            if( (state.dwButtons & 0x01 << 6) ){
                emit onButtonBackChanged(true);
            } else {
                emit onButtonBackChanged(false);
            }
            if( (state.dwButtons & 0x01 << 7) ){
                emit onButtonStartChanged(true);
            } else {
                emit onButtonStartChanged(false);
            }
            if( (state.dwButtons & 0x01 << 8) ){
                emit onButtonLPChanged(true);
            } else {
                emit onButtonLPChanged(false);
            }
            if( (state.dwButtons & 0x01 << 9) ){
                emit onButtonRPChanged(true);
            } else {
                emit onButtonRPChanged(false);
            }

            /// 方向键，待加入其他四个方向。
            /// 考虑到次世代手柄，应该增加更多的适应
            if( state.dwPOV == 0 ){
                emit onButtonUpChanged(true);
            } else {
                emit onButtonUpChanged(false);
            }
            if( state.dwPOV == 9000 ){
                emit onButtonRightChanged(true);
            } else {
                emit onButtonRightChanged(false);
            }
            if( state.dwPOV == 18000) {
                emit onButtonDownChanged(true);
            } else {
                emit onButtonDownChanged(false);
            }
            if( state.dwPOV == 27000) {
                emit onButtonLeftChanged(true);
            } else {
                emit onButtonLeftChanged(false);
            }





        }
    });


}
