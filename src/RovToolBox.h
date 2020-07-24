#ifndef ROVTOOLBOX_H
#define ROVTOOLBOX_H

#include <QObject>
#include <RovControlCore.h>

class RovApplication;
class VideoManager;
class SocketManager;
class SettingManager;
class KeyManager;
class VideoReceiver;

class RovToolBox : public QObject
{
    Q_OBJECT

public:
    RovToolBox(RovApplication * app);
    RovToolBox();
    void setInit();

    SocketManager*  getSocketManager() ;
    KeyManager*     getKeyManager() {return keyManager;}
    VideoManager*   getVideoManager() {return videoManager;}
    SettingManager* getSettingManager();
    RovControlCore* getRovControlCore() { return controler; }

    VideoReceiver* createVideoReceiver(RovToolBox*);
    //AudioOutput* audioOutput () {}

    QString getPort_1(){return this->udp_port_1;}
    QString getPort_2(){return this->udp_port_2;}
    QString getMpegts_uri(){return this->mpegts_uri;}

private:
    SettingManager* settingManager;
    SocketManager* socketManager;
    KeyManager* keyManager;
    VideoManager* videoManager;
    RovControlCore* controler;
    QString uri;
    QString mpegts_uri;
    QString udp_port_1;
    QString udp_port_2;

    friend class RovApplication;
signals:
    void onUriChanged();
    void onUdpPort_1_Changed();
    void onUdpPort_2_Changed();
    void onMpegtsUriChanged();
};



#endif // ROVTOOLBOX_H
