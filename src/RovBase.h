#ifndef ROVBASE_H
#define ROVBASE_H

#include <QObject>
#include "RovApplication.h"
#include "RovToolBox.h"

class RovBase : public QObject
{
    Q_OBJECT
public:
    RovBase(RovApplication* app, RovToolBox* toolbox);
    RovBase(QObject* parent = nullptr);
    virtual void setToolbox(RovToolBox* toolbox);

protected:
    RovApplication* app;
    RovToolBox* toolbox;

};

#endif // ROVBASE_H
