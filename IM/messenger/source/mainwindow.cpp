#include "messenger/mainwindow.h"
#include "ui_mainwindow.h"

#include "messenger/communication.h"
#include "messenger/udp_socket.h"

namespace IM {

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    UdpSocket udpSocket;
    Communication communication(udpSocket);
    connect(ui->pbSend, SIGNAL(clicked()), SLOT(handleSendMessage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::handleSendMessage()
{
    QString message = ui->lineEdit->text();
    emit send_message(_nickname, message);
}

}
