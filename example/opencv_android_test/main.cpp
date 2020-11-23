#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <videomanager.h>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    VideoManager video;

    QQmlApplicationEngine engine;


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);


    engine.rootContext()->setContextProperty("videomanager", &video);
    engine.addImageProvider(QLatin1String("provider"), video.provider);
    qmlRegisterUncreatableType<VideoManager>("Rov.VideoManager", 1, 0, "VideoManager", "Reference only");
    engine.load(url);

    return app.exec();
}
