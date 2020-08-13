#ifndef ROVCONTROLLER_H
#define ROVCONTROLLER_H

#include <QApplication>
#include <QQuickItem>
#include "RovToolbox.h"

class RovApplication : public QApplication
{
    Q_OBJECT
public:
    RovApplication(int& argc, char* argv[]);
    ~RovApplication();

    static RovApplication* _app;

    RovToolbox* getToolbox(){return this->toolbox;}
private:
    void initAppBoot();
    void checkSavePath();
private:
    RovToolbox* toolbox;
};

RovApplication* rovApp(void);


#endif // ROVCONTROLLER_H
