#include "messenger/udp_socket.h"

namespace IM {

UdpSocket::UdpSocket(QObject* parent) :
    _udp_socket(parent)
{            
    connect(&_udp_socket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}

qint64 UdpSocket::writeDatagram(const QByteArray & datagram, const QHostAddress & host, quint16 port)
{
    return _udp_socket.writeDatagram(datagram, host, port);
}


void UdpSocket::readPendingDatagrams()
{
    while (_udp_socket.hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(_udp_socket.pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        _udp_socket.readDatagram(
                        datagram.data(),
                        datagram.size(),
                        &sender,
                        &senderPort);

        emit datagramReceived(datagram);
    }
}

bool UdpSocket::bind ( const QHostAddress & address, quint16 port)
{
    return _udp_socket.bind (address, port, QUdpSocket::ShareAddress);
}


} // IM

