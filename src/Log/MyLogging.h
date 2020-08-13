#ifndef MYLOGGING_H
#define MYLOGGING_H

#include <QObject>

class MyLogging : public QObject
{
    Q_OBJECT
public:
    explicit MyLogging(QObject *parent = nullptr);

    typedef enum
    {
        APPLICATION_LOGGING,
        SETTINGS_LOGGING,
        VIDEO_LOGGING,
        SOCKET_LOGGING,
        RECEIVE_LOGGING,
        SEND_LOGGING,
        KEYBOARD_LOGGING,
        JOYSTICK_LOGGING
    } LOG_TYPE;

    typedef enum{
        INFO,
        DEBUG,
        WARNING
    } LOG_LEVEL;


    static void log(const QString& info, LOG_LEVEL level = INFO, LOG_TYPE type = APPLICATION_LOGGING);

signals:

};

#endif // MYLOGGING_H
