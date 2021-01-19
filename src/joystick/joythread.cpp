#include "joythread.h"
#include <QDebug>

JoyThread::JoyThread(QObject *parent) :
    QThread(parent)
{
}

void JoyThread::send_state_row(joyinfoex_tag state_row) {
    emit JoySignal_row(state_row);
}

void JoyThread::run() {
    joyinfoex_tag state_row;

    openJoy();

    while(1) {
        msleep(JOY_READ_PEROID);
        state_row = joyRead_row();
        send_state_row(state_row);
    }
}
