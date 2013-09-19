#include <QtCore/QDataStream>
#include <QtNetwork/QHostAddress>
#include <QDebug>

#include "messenger/iudp_socket.h"
#include "messenger/communication.h"

namespace IM {

quint32 const Command::KeepAlive    = 0;
quint32 const Command::Message      = 1;
quint32 const Command::HostEvent    = 2;
quint32 const Command::CallOutEvent = 4;

Communication::Communication(IUdpSocket & udp_socket) :
    _udp_socket(udp_socket),
    _port(41000)
{
    connect(&_udp_socket, SIGNAL(datagramReceived(QByteArray&)), SLOT(handle_receive_message(QByteArray&)));   
    _udp_socket.bind(QHostAddress::Broadcast, _port);
}

void Communication::handle_send_message(const QString & nickname, const QString & message)
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_5_0);

    stream << Command::Message;
    stream << nickname;
    stream << message;

    _udp_socket.writeDatagram(data, QHostAddress::Broadcast, _port);
}

void Communication::handle_receive_message(QByteArray &data)
{
    QDataStream stream(&data, QIODevice::ReadOnly);
    stream.setVersion(QDataStream::Qt_5_0);

    quint32 command;
    QString nickname;
    QString message;
    stream >> command >> nickname >> message;

    switch (command) {
     case IM::Command::Message:
        emit received_message(nickname, message);
        break;

    case IM::Command::KeepAlive:
        emit received_keepalive(nickname);
        break;

    case IM::Command::CallOutEvent:
    case IM::Command::HostEvent:
        // take message as "Event" (as both messages are the same format)
        emit received_event(message);
        break;

    default:
        qDebug() << "unknown message received";
        break;
    }

}


void Communication::handle_send_keepalive(QString const & nickname)
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_5_0);

    stream << Command::KeepAlive;
    stream << nickname;

    _udp_socket.writeDatagram(data, QHostAddress::Broadcast, _port);
}

} // IM

