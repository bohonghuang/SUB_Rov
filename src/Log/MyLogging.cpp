#include "MyLogging.h"
#include <QDir>
#include <QTextStream>
#include <QDateTime>
#include <QMutex>
#include <QDebug>
#include <QCoreApplication>

MyLogging::MyLogging(QObject *parent) : QObject(parent)
{

}

QString makeFile(MyLogging::LOG_TYPE type){

    QDir dir;
    QString localPath = QCoreApplication::applicationDirPath();
    QString filePath = localPath + "/temp";
//    qDebug() << localPath;
    if( !dir.exists(filePath) ){
        dir.mkpath(filePath);
    }

    QString filename;
    switch (type) {
    case MyLogging::APPLICATION_LOGGING:
        filename = "ApplicationLogging.txt";
        break;
    case MyLogging::SETTINGS_LOGGING:
        filename = "SettingsLogging.txt";
        break;
    case MyLogging::VIDEO_LOGGING:
        filename = "VideoLogging.txt";
        break;
    case MyLogging::SOCKET_LOGGING:
        filename = "SocketLogging.txt";
        break;
    case MyLogging::RECEIVE_LOGGING:
        filename = "ReceiveLogging.txt";
        break;
    case MyLogging::SEND_LOGGING:
        filename = "SendLogging.txt";
        break;
    case MyLogging::KEYBOARD_LOGGING:
        filename = "KeyboardLogging.txt";
        break;
    case MyLogging::JOYSTICK_LOGGING:
        filename = "JoystickLogging.txt";
        break;
    default:
        filename = "ApplicationLogging.txt";
        break;
    }

    return filePath + "/" + filename;
}

QString getLogLevel(MyLogging::LOG_LEVEL level){
    QString lv;
    switch (level) {
    case MyLogging::INFO:
        lv = "Info";
        break;
    case MyLogging::DEBUG:
        lv = "Debug";
        break;
    case MyLogging::WARNING:
        lv = "Warning";
        break;
    default:
        lv = "Info";
        break;
    }

    return lv;
}

void MyLogging::log(const QString &info, MyLogging::LOG_LEVEL level, MyLogging::LOG_TYPE type)
{
    static QMutex mutex;
    mutex.lock();

    QString fileName = makeFile(type);
    QString currentTime = QDateTime::currentDateTime().toString("yyyy/MM/dd_hh:mm:ss.zzz");
    QString lv = getLogLevel(level);
    QString message = QString("%1:  __%2__  _%3_").arg(lv).arg(info).arg(currentTime);

    QFile file(fileName);

    if(file.open( QIODevice::ReadWrite | QIODevice::Append )){
        QTextStream out(&file);
        out << message << "\r\n";
    }
    file.flush();
    file.close();

    mutex.unlock();
}

