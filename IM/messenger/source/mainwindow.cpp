#include "messenger/mainwindow.h"
#include "ui_mainwindow.h"

#include "messenger/communication.h"
#include "messenger/controller.h"
#include "messenger/usermanager.h"
#include "messenger/udp_socket.h"
#include "messenger/usersmodel.h"
#include "messenger/editdialog.h"

#include <QKeyEvent>

namespace IM
{

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _nickname("MyName"),
    _pController(new Controller()),
    _pCommunication(NULL),
    _pUserManager(new UserManager()),
    _pUdpSocket(NULL),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _pUdpSocket = new UdpSocket();
    _pCommunication = new Communication(*_pUdpSocket);

    connect(_pController, SIGNAL(send_message(QString,QString)), _pCommunication, SLOT(handle_send_message(QString,QString)));
    connect(this, SIGNAL(send_message(QString const &)), _pController, SLOT(handle_send_message(const QString &)));
    connect(_pController, SIGNAL(send_keepalive(QString)), _pCommunication, SLOT(handle_send_keepalive(QString)));

    connect(_pCommunication, SIGNAL(received_message(QString,QString)), _pUserManager, SLOT(received_message(QString const &)));
    connect(_pCommunication, SIGNAL(received_keepalive(QString)), _pUserManager, SLOT(received_message(QString)));

    connect(ui->pbSend, SIGNAL(clicked()), SLOT(handleSendMessage()));
    connect(ui->textMessageInput, SIGNAL(returnPressed()), SLOT(handleSendMessage()));
    ui->textMessageInput->installEventFilter(this);

    connect(_pCommunication, SIGNAL(received_message(QString,QString)),this,SLOT(handleIncommingMessage(QString,QString)));

    connect(ui->pbEditNickname, SIGNAL(clicked()),SLOT(editClicked()));

    updateNickName();

    ui->textMessageInput->setFocus();

    UsersModel* model = new UsersModel(this);
    ui->treeView->setModel(model);
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
    emit send_message(message);
    ui->textMessageInput->clear();
}

void MainWindow::editClicked()
{
    EditDialog dlg(this);
    dlg.setEditData(_nickname);
    if (dlg.exec()==QDialog::Accepted)
    {
        _nickname = dlg.getEditData();
        _pController->set_nickname(_nickname);
        updateNickName();
    }
}

void MainWindow::updateNickName()
{
    ui->lblNickName->setText(_nickname);
    _pController->set_nickname(_nickname);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_D && keyEvent->modifiers() == Qt::ControlModifier)
        {
            emit request_quit();
            return true;
        }
    }
    return QObject::eventFilter(obj, event);
}

}
