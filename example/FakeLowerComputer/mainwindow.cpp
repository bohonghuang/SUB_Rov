#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdio>


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
        ui->lbl_deep_lock->setText( QString::number(socketmanager->getData(DEEP_LOCK)) );
        ui->lbl_direc_lock->setText( QString::number(socketmanager->getData(DIRECTION_LOCK)) );
        ui->lbl_forward_back->setText( QString::number(socketmanager->getData(FORWORD_BACK)) );
        ui->lbl_left_right->setText( QString::number(socketmanager->getData(LEFT_RIGHT)) );
        ui->lbl_up_down->setText( QString::number(socketmanager->getData(UP_DOWN)) );
        ui->lbl_spin->setText( QString::number(socketmanager->getData(SPIN)) );
        ui->lbl_light->setText( QString::number(socketmanager->getData(LIGHT)) );
        ui->lbl_camera->setText( QString::number(socketmanager->getData(CAMERA)) );
        ui->lbl_cloud->setText( QString::number(socketmanager->getData(CLOUD)) );
        ui->lbl_mutip->setText( QString::number(socketmanager->getData(MULTIP)) );
        ui->lbl_pi->setText( QString::number(socketmanager->getData(PI)) );
        ui->lbl_soup->setText( QString::number(socketmanager->getData(SOUP)) );

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
    socketmanager->setSendData(DEEP, ui->input_deep->text().toDouble());
    socketmanager->setSendData(VOLTAGE, ui->inp_voltage->text().toDouble());
    socketmanager->setSendData(INSIDE_TEMPERATURE, ui->inp_temp_in->text().toDouble());
    socketmanager->setSendData(OUTSIDE_TEMPERATURE, ui->inp_temp_out->text().toDouble());
    socketmanager->setSendData(YAW, ui->inp_yaw->text().toDouble());
    socketmanager->setSendData(PITCH, ui->inp_pitch->text().toDouble());
    socketmanager->setSendData(ROLL, ui->inp_roll->text().toDouble());
    socketmanager->setSendData(SPEED, ui->input_speed->text().toDouble());
    socketmanager->setSendData(STATE, ui->inp_state->text().toDouble());

    socketmanager->startTimer();
}
