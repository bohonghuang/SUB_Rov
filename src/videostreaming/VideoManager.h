#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include <QObject>
#include "VideoReceiver.h"
#include "ImageProvider.h"

class VideoManager : public QObject
{
    Q_OBJECT
public:
    explicit VideoManager(QObject *parent = nullptr);

    void setUrl(const QString& url);
    void updateSettings();

    VideoReceiver* getReceiver(){return  this->videoReceiver; }
    VideoReceiver* getThermalReceiver(){return this->videoReceiver_sencond;}
    ImageProvider* getProvider() {return this->videoReceiver->getProvider();}
    ImageProvider* getThermalProvider() {return this->videoReceiver_sencond->getProvider(); }
public slots:
    void startVideo();
    void stopVideo();
    void restartVideo();
    void startRecord();
    void stopRecord();
    void grabImage();

private:
    bool recording;
    bool playing;

    QString url;

    VideoReceiver* videoReceiver;
    VideoReceiver* videoReceiver_sencond;

signals:
    void recordingChanged();
    void openedChanged();
    void thermalOpenedChanged();

};

#endif // VIDEOMANAGER_H
