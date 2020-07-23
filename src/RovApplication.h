#ifndef ROVAPPLICATION_H
#define ROVAPPLICATION_H

#include <QTimer>
#include <QQmlApplicationEngine>
#include <QTranslator>
#include <QQuickItem>
#include <QElapsedTimer>
#include <QApplication>
#include "RovToolBox.h"

class RovApplication : public QApplication
{
    Q_OBJECT
public:
    RovApplication(int& argc, char* argv[]);
    ~RovApplication();
    static RovApplication* _app;
    void showMessage(const QString&message);
    Q_INVOKABLE void openVideoSettingWindow();
    void setToolbox(RovToolBox* tool){this->toolbox = tool;}
    RovToolBox* getToolbox()        {return this->toolbox;}
    bool isBluetoothAvailable()     {return this->bluetoothAvailable;}
    bool isSettingsGroupVisible()   {return this->settingsGroupVisible; }
    bool isInternetAvailable();

    void setLanguage();
    QQuickItem* MainRootWindow();

public slots:
    //void showSetupView();

    const QLocale getCurrentLanguage() {return this->locale;}

signals:
    void languageChanged(const QLocale locale);

public:
    void initCommon();
    bool initAppBoot();

    bool isErrorState(){return this->error;}

public:
    void shutdown();
    bool checkTelemetrySavePath(bool useMessageBox);

private slots:
    bool pareseVersionText(const QString& versionString,
                           int & majorVersion,
                           int & minorVersion,
                           int & buildVersion);

private:
    QObject * rootQmlObject ();
    virtual void checkForNewVersion();
    void emitWithError(QString errorMessage);

    QTimer  missingParamsDelayedDisplayTimer;
    QList<QPair<int, QString>> missingParams;

    QQmlApplicationEngine* qmlAppEngine = nullptr;
    bool logOutput                      = false;
    bool fakeMobile             = false;
    bool settingUpgraded        = false;
    bool settingsGroupVisible   = false;
    bool bluetoothAvailable     = false;
    RovToolBox *toolbox         = nullptr;

    QTranslator RTranslator;
    QTranslator RTranslatorQt;
    QQuickItem* mainRootWindow  = nullptr;

    QLocale locale;
    bool error                  = false;
    QElapsedTimer msecsElapsedTime;

    QList<QPair<QString /*title*/, QString /*message*/>> delayedAppMessages;
public:
};

RovApplication * rovApp(void);


#endif // ROVAPPLICATION_H
