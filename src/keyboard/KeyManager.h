#ifndef KEYMANAGER_H
#define KEYMANAGER_H

#include <QObject>
#include "../Log/MyLogging.h"


class KeyLogging: public MyLogging
{
public:
    void info(const QString& msg ){ log(msg, INFO, KEYBOARD_LOGGING); }
    void debug(const QString& msg ){ log(msg, DEBUG, KEYBOARD_LOGGING); }
    void warning(const QString& msg ){ log(msg, WARNING, KEYBOARD_LOGGING); }
};


class KeyManager : public QObject
{
    Q_OBJECT
public:
    KeyManager();
    ~KeyManager();

    Q_INVOKABLE void doThings(Qt::Key key);
    Q_INVOKABLE void doRelease(Qt::Key key);

private:
    KeyLogging log;
signals:

};

#endif // KEYMANAGER_H
