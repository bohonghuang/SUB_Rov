#ifndef SETTINGMANAGER_H
#define SETTINGMANAGER_H

#include <QObject>
#include <QSettings>
#include <QDateTime>

#include "RovApplication.h"
#include "RovToolBox.h"
#include "VideoManager.h"



class SettingManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString uri READ getServerUri WRITE setServerUri NOTIFY onServerUriChanged)
    Q_PROPERTY(QString port READ getServerPort WRITE setServerPort NOTIFY onServerPortChanged)
    Q_PROPERTY(QString video_uri READ getVideoPort WRITE setVideoUrl NOTIFY onVideoUriChanged)
    Q_PROPERTY(QString video_port READ getVideoUrl WRITE setVideoPort NOTIFY onVideoPortChanged())
public:
    SettingManager();
    ~SettingManager();
    void InitSettings();

    Q_INVOKABLE QString getServerUri()  {return uri;}
    Q_INVOKABLE QString getServerPort() {return port;}
    Q_INVOKABLE QString getVideoPort()  {return this->video_port;  };
    Q_INVOKABLE QString getVideoUrl()   {return this->video_uri;   };
    Q_INVOKABLE QString getThermalVideoPort()  {return this->thermal_video_port;  };
    Q_INVOKABLE QString getThermalVideoUrl()   {return this->thermal_video_uri;   };
    Q_INVOKABLE QString getAudioPort()  {return this->audio_port;  };
    Q_INVOKABLE QString getAudioUrl()   {return this->audio_uri;   };
    Q_INVOKABLE int     getStreamType() {return this->stream_type; };
    Q_INVOKABLE int     getStreamType_2() {return this->stream_type_2; };
    Q_INVOKABLE QString getVideoPath()  {return this->videoSavePath; };
    Q_INVOKABLE QString getImagePath();

    typedef enum {
        UDP265,
        UDP264,
        TCP
    } STREAMING_TYPE;
public :
    Q_INVOKABLE void setServerUri(QString u);
    Q_INVOKABLE void setServerPort(QString p);
    Q_INVOKABLE void setVideoUrl(const QString u);
    Q_INVOKABLE void setVideoPort(const QString p);
    Q_INVOKABLE void setThermalVideoUrl(const QString u);
    Q_INVOKABLE void setThermalVideoPort(const QString p);
    Q_INVOKABLE void setAudioUrl(const QString u);
    Q_INVOKABLE void setAudioPort(const QString p);
    Q_INVOKABLE void setStreamType(const int t = STREAMING_TYPE::UDP265);
    Q_INVOKABLE void setStreamType_2(const int t = STREAMING_TYPE::UDP265);
    Q_INVOKABLE void udpSettings();
private:
    QString uri;
    QString port;

    QString video_uri;
    QString video_port;
    QString thermal_video_uri;
    QString thermal_video_port;
    QString audio_uri;
    QString audio_port;

    QSettings* read_write;

    QString videoSavePath;
    QString grapImageSavePath;

    STREAMING_TYPE stream_type;
    STREAMING_TYPE stream_type_2;

    int win_x;
    int win_y;
    int win_w;
    int win_h;
signals:
    void onServerUriChanged();
    void onServerPortChanged();
    void onVideoUriChanged();
    void onVideoPortChanged();
};

#endif // SETTINGMANAGER_H
