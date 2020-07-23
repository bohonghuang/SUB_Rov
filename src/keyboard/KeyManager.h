#ifndef KEYMANAGER_H
#define KEYMANAGER_H

#include <QObject>

class KeyManager : public QObject
{
    Q_OBJECT
public:
    KeyManager();
    ~KeyManager();

    Q_INVOKABLE void doThings(Qt::Key key);
    Q_INVOKABLE void doRelease(Qt::Key key);
signals:

};

#endif // KEYMANAGER_H
