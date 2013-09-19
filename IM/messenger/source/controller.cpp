#include "messenger/controller.h"
#include <QTimer>
#include <QDebug>

namespace IM {

Controller::Controller() :
    QObject()
   , _nickname("")
  , _pTimer(new QTimer(this))
{
    connect(_pTimer, SIGNAL(timeout()), this, SLOT(handle_timeout()));
    _pTimer->start(TIMEOUT);
    qDebug() << "Timer started...";
}

void Controller::handle_send_message(const QString & message)
{
    emit send_message(_nickname, message);
}

void Controller::set_nickname(const QString & nickname)
{
    _nickname = nickname;
}


void Controller::handle_timeout()
{
    qDebug() << "Timeout!";
    emit send_keepalive(_nickname);
}

} // IM

