#ifndef JOYTHREAD_H
#define JOYTHREAD_H

#include <QThread>
#include "joysticker.h"

// 周期 100ms
#define JOY_READ_PEROID 100

class JoyThread : public QThread
{
    Q_OBJECT
public:
    explicit JoyThread(QObject*parent = 0);
signals:
    void JoySignal_row(joyinfoex_tag);
protected:
    void run();
    void send_state_row(joyinfoex_tag state_row);
};

#endif // JOYTHREAD_H
