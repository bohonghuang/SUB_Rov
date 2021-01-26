#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    socketmanager = new SocketManager();
    socketmanager->setURI(ui->inp_send_ip->text());
    socketmanager->setPort(ui->inp_send_port->text().toInt());
    socketmanager->setRecvPort(ui->inp_recv_port->text().toInt());
    socketmanager->setTimerTime(ui->inp_timer_num->text().toInt()*1000);

    connect(socketmanager, &SocketManager::dataChanged, this, [=](){

        ui->lbl_voltage->setText( QString::number(socketmanager->getData(VOLTAGE)));
        ui->lbl_temp_out->setText( QString::number(socketmanager->getData(OUTSIDE_TEMPERATURE)));
        ui->lbl_temp_in->setText( QString::number(socketmanager->getData(INSIDE_TEMPERATURE)));
        ui->lbl_deep->setText( QString::number(socketmanager->getData(DEEP)));
        ui->lbl_yaw->setText( QString::number(socketmanager->getData(YAW)));
        ui->lbl_pitch->setText( QString::number(socketmanager->getData(PITCH)));
        ui->lbl_roll->setText( QString::number(socketmanager->getData(ROLL)));
        ui->lbl_speed->setText( QString::number(socketmanager->getData(SPEED)));
        ui->lbl_state->setText( QString::number(socketmanager->getData(STATE)));

    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_inp_send_ip_textChanged(const QString &arg1)
{
    socketmanager->setURI(arg1);
}

void MainWindow::on_inp_send_port_textChanged(const QString &arg1)
{
    socketmanager->setPort(arg1.toUInt());
}

void MainWindow::on_inp_recv_port_textChanged(const QString &arg1)
{
    socketmanager->setRecvPort(arg1.toUInt());
}

void MainWindow::on_inp_timer_num_textChanged(const QString &arg1)
{
    socketmanager->setTimerTime(arg1.toInt() * 1000);
}

void MainWindow::on_pushButton_3_clicked()
{
    socketmanager->disconnectServer();
}

void MainWindow::on_pushButton_2_clicked()
{
    socketmanager->connectServer();
}

void MainWindow::on_pushButton_clicked()
{
    socketmanager->setSendData(DEEP_LOCK, ui->txt_deep_lock->text().toDouble());
    socketmanager->setSendData(DIRECTION_LOCK, ui->txt_direct_lock->text().toDouble());
    socketmanager->setSendData(FORWORD_BACK, ui->txt_forward_back->text().toDouble());
    socketmanager->setSendData(LEFT_RIGHT, ui->txt_left_right->text().toDouble());
    socketmanager->setSendData(UP_DOWN, ui->txt_up_down->text().toDouble());
    socketmanager->setSendData(SPIN, ui->txt_spin->text().toDouble());
    socketmanager->setSendData(OIL, ui->txt_oil->text().toDouble());
    socketmanager->setSendData(LIGHT, ui->txt_light->text().toDouble());
    socketmanager->setSendData(CAMERA, ui->txt_camera->text().toDouble());
    socketmanager->setSendData(CLOUD, ui->txt_cloud->text().toDouble());
    socketmanager->setSendData(MULTIP, ui->txt_multip->text().toDouble());
    socketmanager->setSendData(PI, ui->txt_pi->text().toDouble());
    socketmanager->setSendData(SOUP, ui->txt_soup->text().toDouble());
    socketmanager->setSendData(START_STOP, ui->txt_start_stp->text().toDouble());

    socketmanager->startTimer();
}
