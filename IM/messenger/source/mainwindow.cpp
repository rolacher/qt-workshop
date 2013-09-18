#include "messenger/mainwindow.h"
#include "ui_mainwindow.h"

#include "messenger/communication.h"
#include "messenger/controller.h"
#include "messenger/usermanager.h"
#include "messenger/eventmanager.h"
#include "messenger/udp_socket.h"
#include "messenger/usersmodel.h"
#include "messenger/editdialog.h"
#include "messenger/nickname.h"

#include <QKeyEvent>

namespace IM
{

const QString MainWindow::_persistFilename = "messenger.ini";


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _pController(new Controller()),
    _pCommunication(NULL),
    _pUserManager(new UserManager()),
    _pUsersModel(new UsersModel(this, _pUserManager)),
    _pEventManager(new EventManager()),
    _pUdpSocket(NULL),
    _nickName(NULL),
    ui(new Ui::MainWindow)
{ 
    _nickName = new NickName(_persistFilename);

    ui->setupUi(this);

    _pUdpSocket = new UdpSocket();
    _pCommunication = new Communication(*_pUdpSocket);

    connect(_pController, SIGNAL(send_message(QString,QString)), _pCommunication, SLOT(handle_send_message(QString,QString)));
    connect(this, SIGNAL(send_message(QString const &)), _pController, SLOT(handle_send_message(const QString &)));
    connect(_pController, SIGNAL(send_keepalive(QString)), _pCommunication, SLOT(handle_send_keepalive(QString)));

    connect(_pCommunication, SIGNAL(received_message(QString,QString)), _pUserManager, SLOT(received_message(QString const &)));
    connect(_pCommunication, SIGNAL(received_keepalive(QString)), _pUserManager, SLOT(received_message(QString)));

    connect(_pCommunication, SIGNAL(received_event(QString)), _pEventManager, SLOT(received_event(QString)));

    connect(ui->pbSend, SIGNAL(clicked()), SLOT(handleSendMessage()));
    connect(ui->textMessageInput, SIGNAL(returnPressed()), SLOT(handleSendMessage()));
    ui->textMessageInput->installEventFilter(this);

    connect(_pCommunication, SIGNAL(received_message(QString,QString)),this,SLOT(handleIncommingMessage(QString,QString)));

    connect(ui->pbEditNickname, SIGNAL(clicked()),SLOT(editClicked()));

    connect(_pUserManager, SIGNAL(UserListChanged()), _pUsersModel, SLOT(handle_user_list_changed()));

    updateNickName();

    ui->textMessageInput->setFocus();

    ui->treeView->setModel(_pUsersModel);
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
    dlg.setEditData(_nickName->getNickname());
    if (dlg.exec()==QDialog::Accepted)
    {
        _nickName->setNickname(dlg.getEditData());
        updateNickName();
    }
}

void MainWindow::updateNickName()
{
    const QString name = _nickName->getNickname();
    ui->lblNickName->setText(name);
    _pController->set_nickname(name);
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
