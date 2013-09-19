#include "messenger/mainwindow.h"
#include "ui_mainwindow.h"

#include "messenger/communication.h"
#include "messenger/controller.h"
#include "messenger/udp_socket.h"

namespace IM {

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _nickname("MyName"),
    _pController(new Controller()),
    _pCommunication(NULL),
    _pUdpSocket(NULL),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _pUdpSocket = new UdpSocket();
    _pCommunication = new Communication(*_pUdpSocket);

    connect(this, SIGNAL(send_message(const QString &, QString const &)), _pController, SLOT(handle_send_message(const QString &)));
    connect(_pController, SIGNAL(send_keepalive(QString)), _pCommunication, SLOT(handle_send_keepalive(QString)));

    connect(ui->pbSend, SIGNAL(clicked()), SLOT(handleSendMessage()));
    connect(ui->textMessageInput, SIGNAL(returnPressed()), SLOT(handleSendMessage()));
}

MainWindow::~MainWindow()
{
    delete _pCommunication;
    delete _pController;
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
