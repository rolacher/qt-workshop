#include <QtCore/QDataStream>
#include <QtNetwork/QHostAddress>
#include <QDebug>

#include "messenger/iudp_socket.h"
#include "messenger/communication.h"

namespace IM {

quint32 const Command::KeepAlive = 0;
quint32 const Command::Message = 1;

Communication::Communication(IUdpSocket & udp_socket) :
    _udp_socket(udp_socket),
    _port(41000)
{
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
    default:
        qDebug() << "unknown message received";
        break;
    }

}

} // IM

