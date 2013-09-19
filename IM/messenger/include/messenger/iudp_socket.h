#ifndef IUDP_SOCKET_H
#define IUDP_SOCKET_H

#include <QtCore/QtGlobal>

class QHostAddress;
class QByteArray;

namespace IM {

class IUdpSocket
{
public:
    ~IUdpSocket() {}

    virtual qint64 writeDatagram(QByteArray const & datagram, QHostAddress const & host, quint16 port) = 0;
    //virtual qint64 readDatagram(QByteArray const & datagram, qint64 maxsize, QHostAddress const & host, quint16 port) = 0;
};

} // IM

#endif // IUDP_SOCKET_H
