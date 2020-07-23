#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QObject>
#include <QLibrary>
#include <QString>

#define JSX  JOYSTICKID1


class JoyStick : public QObject
{
    Q_OBJECT
public:
    explicit JoyStick(QObject *parent = nullptr);

signals:

};

#endif // JOYSTICK_H
