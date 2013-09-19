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
    connect(ui->textMessageInput, SIGNAL(returnPressed()), SLOT(handleSendMessage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleIncommingMessage(const QString& from_nickname, const QString& message)
{
    ui->textChatHistory->append(QString("%1: %2").arg(from_nickname, message));
}

void MainWindow::handleSendMessage()
{
    QString message = ui->textMessageInput->text();
    emit send_message(_nickname, message);
    handleIncommingMessage(_nickname, message);
    ui->textMessageInput->clear();
}

}
