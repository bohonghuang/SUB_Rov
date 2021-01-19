#include "joysticksettings.h"
#include <QDir>
JoyStickSettings::JoyStickSettings(QObject *parent) : QObject(parent)
{
    QString path = QDir::homePath();
    path += ".sub/conf";
    this->settings = new QSettings(path + "/joy.ini", QSettings::IniFormat);

    initMap();
    load();

}

JoyStickSettings::~JoyStickSettings(){
    save();
    delete settings;
}

int JoyStickSettings::setValue(SETTING_JOY_DO key, CONTROLLER_BUTTON value)
{
    if( binding.contains(key) )
         binding[key] = value;
    else
        return 0;
    return 1;
}

CONTROLLER_BUTTON JoyStickSettings::getValue(SETTING_JOY_DO dos)
{
    if( binding.contains(dos) )
        return binding[dos];
    else
        return (CONTROLLER_BUTTON) 0;
}

SETTING_JOY_DO JoyStickSettings::getKey(CONTROLLER_BUTTON cb)
{
    int res = 0;
    for( int i=MIN_DO+1; i<MAX_DO; i++ ){
        if( getValue((SETTING_JOY_DO)i) == cb ){
            res = i;
            break;
        }
    }
    return (SETTING_JOY_DO) res;
}

void JoyStickSettings::initMap() {

    for( int i = (int)MIN_DO + 1 ; i<(int) MAX_DO; i++ ){
        binding.insert( (SETTING_JOY_DO) i , (CONTROLLER_BUTTON) i);
    }

}

CONTROLLER_BUTTON JoyStickSettings::getValueOfSettings(SETTING_JOY_DO dos)
{
    QString tmp;
    settings->beginGroup("settings");
    tmp = settings->value(QString::number(dos)).toString();
    if( tmp.isEmpty()  ){
        tmp = QString::number(binding.value(dos));
        settings->setValue(QString::number(dos),  tmp);
    }
    settings->endGroup();

    return (CONTROLLER_BUTTON) tmp.toInt() ;
}

void JoyStickSettings::save()
{
    settings->beginGroup("settings");
    for( int i = (int)MIN_DO + 1 ; i<(int) MAX_DO; i++ ){
         settings->setValue(QString::number(i),  binding[(SETTING_JOY_DO)i]);
    }
    settings->endGroup();
}

void JoyStickSettings::load()
{
    for( int i = (int)MIN_DO + 1 ; i<(int) MAX_DO; i++ ){
        binding[(SETTING_JOY_DO)i] = getValueOfSettings((SETTING_JOY_DO)i);
    }
}
