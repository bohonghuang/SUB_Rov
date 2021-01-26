#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#define MaxData_Length 26


typedef enum {
    VOLTAGE,
    INSIDE_TEMPERATURE,
    OUTSIDE_TEMPERATURE,
    DEEP,
    YAW,
    PITCH,
    ROLL,
    SPEED,
    STATE
} Send_Type;

typedef enum {
    DEEP_LOCK,
    DIRECTION_LOCK,
    FORWORD_BACK,
    LEFT_RIGHT,
    UP_DOWN,
    SPIN,
    OIL,
    LIGHT,
    CAMERA,
    CLOUD,
    MULTIP,
    PI,
    SOUP

} Recv_Type;

///
/// \brief The SocketManager class
/// 职责：接受、发送、建立连接、断开连接、
class SocketManager : public QObject
{
    Q_OBJECT
public:
    explicit SocketManager(QObject *parent = nullptr);

public slots:
    int received() ;
    int send() ;
    int startTimer();

    int connectServer();
    int disconnectServer();


    int getData(Recv_Type rt);
    int setSendData(Send_Type st, double value);
    int setURI(QString u) { this->_uri = u; return 1;};
    int setPort(quint16 p) { this->_port = p; return 1;};
    int setRecvPort(quint16 p) {this->_recv_port = p; return 1; };
    int setTimerTime(int s) {this->timer_time = s; return 1; };
    quint8* getDataArray() { return this->data; }


private:
    bool canSend;
    bool canRevd;
    QUdpSocket* socket;
    QTimer* timer;

    QString _uri;
    quint16 _port;
    quint16 _recv_port;
    int timer_time;

    quint8 send_data[MaxData_Length];
    quint8 data[MaxData_Length];

signals:
    void dataChanged();
};

#endif // SOCKETMANAGER_H
