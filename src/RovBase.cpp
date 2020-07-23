#include "RovBase.h"

RovBase::RovBase(RovApplication* app, RovToolBox* toolbox)
    : QObject(toolbox)
    , app(app)
    , toolbox(nullptr)

{

}
RovBase::RovBase(QObject *parent ):QObject(parent)
{

}

void RovBase::setToolbox(RovToolBox *toolbox)
{
    this->toolbox = toolbox;
}
