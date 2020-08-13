#include "VideoManager.h"
#include "../Settings/SettingsManager.h"
#include "../RovApplication.h"


VideoManager::VideoManager(QObject *parent) : QObject(parent)
{
    this->videoReceiver = new VideoReceiver();
    this->videoReceiver_sencond = new VideoReceiver();
    this->provider = new ImageProvider();
}

void VideoManager::setUrl(const QString &url)
{
    this->url = url;
}

void VideoManager::updateSettings()
{
    switch (rovApp()->getToolbox()->getSettingsManager()->getStreamType()) {
    case SettingsManager::UDP264:
        this->videoReceiver->setTypeStream(VideoReceiver::GSTREAMER_UDP_264);
        this->videoReceiver->setPort(rovApp()->getToolbox()->getSettingsManager()->getVideoPort());
        break;
    case SettingsManager::UDP265:
        this->videoReceiver->setTypeStream(VideoReceiver::GSTREAMER_UDP_265);
        this->videoReceiver->setPort(rovApp()->getToolbox()->getSettingsManager()->getVideoPort());
        break;
    case SettingsManager::TCP:
        this->videoReceiver->setTypeStream(VideoReceiver::MPEG_TCP);
        this->videoReceiver->setUrl(rovApp()->getToolbox()->getSettingsManager()->getVideoUrl());
        break;
    default:
        qWarning("Not found stream type!!");
        break;
    }

    switch (rovApp()->getToolbox()->getSettingsManager()->getStreamType()) {
    case SettingsManager::UDP264:
        this->videoReceiver_sencond->setTypeStream(VideoReceiver::GSTREAMER_UDP_264);
        this->videoReceiver_sencond->setPort(rovApp()->getToolbox()->getSettingsManager()->getVideoPort());
        break;
    case SettingsManager::UDP265:
        this->videoReceiver_sencond->setTypeStream(VideoReceiver::GSTREAMER_UDP_265);
        this->videoReceiver_sencond->setPort(rovApp()->getToolbox()->getSettingsManager()->getVideoPort());
        break;
    case SettingsManager::TCP:
        this->videoReceiver_sencond->setTypeStream(VideoReceiver::MPEG_TCP);
        this->videoReceiver_sencond->setUrl(rovApp()->getToolbox()->getSettingsManager()->getVideoUrl());
        break;
    default:
        qWarning("Not found stream type!!");
        break;
    }
}

void VideoManager::startVideo()
{
    if(this->videoReceiver){
        this->videoReceiver->startVideo();
        this->videoReceiver->start();
    }
    if(this->videoReceiver_sencond){
        this->videoReceiver_sencond->startVideo();
        this->videoReceiver_sencond->start();
    }
}

void VideoManager::stopVideo()
{
    if(this->videoReceiver){
        this->videoReceiver->stopVideo();
    }
    if(this->videoReceiver_sencond){
        this->videoReceiver_sencond->stopVideo();
    }
}

void VideoManager::grabImage()
{

    this->videoReceiver->grabImage();
    this->videoReceiver_sencond->grabImage();

}
