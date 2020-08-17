#ifndef SETTINGMANAGER_H
#define SETTINGMANAGER_H

#include <QObject>
#include <QSettings>
#include <QDateTime>
#include <QThread>
#include <QDir>
#include <QMutex>

#include <MyLogging.h>

class SettingsLoggging;
class SettingsManager : public QThread
{
    Q_OBJECT
    Q_PROPERTY(QString uri        READ      getServerUri    WRITE setServerUri  NOTIFY serverUriChanged)
    Q_PROPERTY(QString port       READ      getServerPort   WRITE setServerPort NOTIFY serverPortChanged)
    Q_PROPERTY(QString video_uri  READ      getVideoPort    WRITE setVideoUrl   NOTIFY videoUriChanged)
    Q_PROPERTY(QString video_port READ      getVideoUrl     WRITE setVideoPort  NOTIFY videoPortChanged)
    Q_PROPERTY(bool    info       READ      getInfo        NOTIFY infoChanged)
    Q_PROPERTY(bool    enableCheckout READ  isEnableCheckout NOTIFY checkoutChanged)

public:
    SettingsManager();
    ~SettingsManager();
    void InitSettings();


    void run() override;

    bool getInfo(){return info ;};

    typedef enum {
        UDP265,
        UDP264,
        TCP
    } STREAMING_TYPE;


public slots:
    void setServerUri(QString u);
    void setServerPort(QString p);
    void setVideoUrl(const QString u);
    void setVideoPort(const QString p);
    void setThermalVideoUrl(const QString u);
    void setThermalVideoPort(const QString p);
    void setAudioUrl(const QString u);
    void setAudioPort(const QString p);
    void setStreamType(const int t = STREAMING_TYPE::UDP265);
    void setStreamType_2(const int t = STREAMING_TYPE::UDP265);
    void udpSettings();
    void setEnableCheckout(const bool enable);
    void setLowMode(bool mode);
    void setEnableMainVideo(bool enable);
    void setEnableThermal(bool enable);
    void setWindowWidth(int width);
    void setWindowHeight(int height);
    void setThermalWidth(int width){this->thermal_w = width;};
    void setThermalHeight(int height){this->thermal_h = height;};

    QString getServerUri()  {return uri;}
    QString getServerPort() {return port;}
    QString getVideoPort()  {return this->video_port;  };
    QString getVideoUrl()   {return this->video_uri;   };
    QString getThermalVideoPort()  {return this->thermal_video_port;  };
    QString getThermalVideoUrl()   {return this->thermal_video_uri;   };
    QString getAudioPort()  {return this->audio_port;  };
    QString getAudioUrl()   {return this->audio_uri;   };
    int     getStreamType() {return this->stream_type; };
    int     getStreamType_2() {return this->stream_type_2; };
    QString getVideoPath();
    QString getImagePath();
    bool    isEnableCheckout() {return this->enableCheck;}
    bool    isLowMode(){    return this->lowMode;   }
    bool    isEnableMainVideo(){return this->enableMainVideo; }
    bool    isEnableThermal(){return this->enableThermal;  }

    int     getWinWidth() {return this->win_w;}
    int     getWinHeight() {return this->win_h; }
    int     getThermalWidth(){return this->thermal_w;}
    int     getThermalHeight(){return this->thermal_h;}

private:
    bool info;

    bool enableMainVideo;
    bool enableThermal;
    bool enableCheck;
    bool lowMode;

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

    int thermal_w;
    int thermal_h;

    SettingsLoggging* log;

signals:
    void serverUriChanged();
    void serverPortChanged();
    void videoTypeChanged();
    void videoUriChanged();
    void videoPortChanged();
    void thermalVideoTypeChanged();
    void thermalVideoUriChanged();
    void thermalVideoPortChanged();
    void infoChanged();
    void checkoutChanged();
    void lowModeChanged();

    void winWidthChanged();
    void winHeightChanged();

    void enableMainChanged();
    void enableThermalChanged();
};

class SettingsLoggging: public MyLogging
{
public:
    void info(const QString& msg ){ log(msg, INFO, SETTINGS_LOGGING); }
    void debug(const QString& msg ){ log(msg, DEBUG, SETTINGS_LOGGING); }
    void warning(const QString& msg ){ log(msg, WARNING, SETTINGS_LOGGING); }
};

#endif // SETTINGMANAGER_H
