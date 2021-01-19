#ifndef JOYSTICKSETTINGS_H
#define JOYSTICKSETTINGS_H

#include <QObject>
#include <QMap>
#include <QSettings>

#include "../joystick/joystickmanager.h"

typedef enum {
    MIN_DO,
    ADD_OIL,
    SUB_OIL,
    ENLARGE_LIGHT,
    REDUCE_LIGHT,
    ENLARGE_FOCUSING,
    REDUCE_FOCUSING,
    ENLARGE_ZOOMING,
    REDUCE_ZOOMING,
    UP_CLOUD,
    DOWN_CLOUD,
    LOCK_DEEP,
    LOCK_DIRECTION,
    MAX_DO

} SETTING_JOY_DO;

class JoyStickSettings : public QObject
{
    Q_OBJECT
public:
    explicit JoyStickSettings(QObject *parent = nullptr);
    ~JoyStickSettings();
    int setValue(SETTING_JOY_DO, CONTROLLER_BUTTON);
    CONTROLLER_BUTTON getValue(SETTING_JOY_DO);
    SETTING_JOY_DO getKey(CONTROLLER_BUTTON);
private:
    void initMap();
    CONTROLLER_BUTTON getValueOfSettings(SETTING_JOY_DO) ;
    void save();
    void load();

    QMap<SETTING_JOY_DO, CONTROLLER_BUTTON> binding;
    QSettings* settings;

signals:

};

#endif // JOYSTICKSETTINGS_H
