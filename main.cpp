#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QIODevice>
#include <QFile>
#include "RovApplication.h"

//这是一个自定的日志详细输出 Handler
void MessageOutput(QtMsgType type, const QMessageLogContext & context, const QString& msg);


int main(int argc, char *argv[])
{
    //check_log_file();
    qInstallMessageHandler(MessageOutput);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    RovApplication* app = new RovApplication(argc, argv);

    int exitCode = 0;
    if(!app->initAppBoot()){
        return -1;
    }

    exitCode = app->exec();


    app->shutdown();
    delete app;

    qDebug() << "After app delete";

    return exitCode;
}

void MessageOutput(QtMsgType type, const QMessageLogContext & context, const QString& msg)
{
    // 使用 QMutex进行加锁、解锁操作，便于可以安全的在多线程操作中使用。
    // QFile 打开模式为 QIODevice::ReadWrite | QIODevice::Append（读写、追加模式），
    // 保证了输出信息可以以追加的形式写入文件。
    static QMutex mutex;
    mutex.lock();

    QByteArray localMsg = msg.toLocal8Bit();
    QString text = QString("[");
    switch (type) {
    case QtDebugMsg:
        text += "Debug: ";
        break;
    case QtInfoMsg:
        text += "Info: ";
        break;
    case QtWarningMsg:
        text += "Warning: ";
        break;
    case QtCriticalMsg:
        text += "Critical: ";
        break;
    case QtFatalMsg:
        text += "Fatal: ";
        break;
    }
    text += "]";

    QString current_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");


    QString message = QString("%1 [__Time:%2__] [__Function:(%4)__] [__Line:%5__] [__%3__]")
            .arg(text).arg(current_time).arg(localMsg.constData())
            .arg(context.function).arg(context.line);

    //输出信息至文件，（读写、追加模式）
    QDir dir;
    QString appPath = dir.currentPath();
    QString resourcePath = appPath + "/tmp";
    QString logPath =  resourcePath + "/log.txt";

    if( !dir.exists(resourcePath)){
        dir.mkpath(resourcePath);
    }
    QFile file;
    file.setFileName("./tmp/log.txt");
    file.open(QIODevice::WriteOnly |  QIODevice::Append);

    QTextStream textstream(&file) ;
    textstream << message << "\r\n";
    file.flush();
    file.close();

    fprintf(stderr, "%s \n",message.toStdString().data() );
    mutex.unlock();

}
