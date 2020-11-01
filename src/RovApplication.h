/*
 * RovApplication是用于建立rov应用程序的主类
 *
 * */
#ifndef ROVCONTROLLER_H
#define ROVCONTROLLER_H

#include <QApplication>
#include "RovToolbox.h"

class RovApplication : public QApplication
{
    Q_OBJECT
public:
    RovApplication(int& argc, char* argv[]);
    ~RovApplication();

    static RovApplication* _app;

//    RovApplication *getThis();
    RovToolbox* getToolbox(){return this->toolbox;}

private:
    RovToolbox* toolbox;
//    QThread* myThread;
    void initAppBoot();
    void checkSavePath();
};

RovApplication* rovApp(void);


#endif // ROVCONTROLLER_H
