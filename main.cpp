#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <RovApplication.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    RovApplication* app = new RovApplication(argc, argv);


    return app->exec();
}
