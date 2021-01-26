#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "socketmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    SocketManager* socketmanager;
private slots:
    void on_inp_send_ip_textChanged(const QString &arg1);

    void on_inp_send_port_textChanged(const QString &arg1);

    void on_inp_recv_port_textChanged(const QString &arg1);

    void on_inp_timer_num_textChanged(const QString &arg1);

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
