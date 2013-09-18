#include <QtCore/QByteArray>

#include "qudpsocket_mock.h"

qint64 QUdpSocketMock::writeDatagram(QByteArray const & datagram, QHostAddress const & host, quint16 port)
{
    emit called_writeDatagram(datagram, host, port);
    return datagram.size();
}
qint64 QUdpSocketMock::readDatagram(QByteArray const & datagram, qint64 maxsize, QHostAddress const & host, quint16 port)
{
     emit called_readDatagram(datagram, maxsize, host, port);
     return datagram.size();
}

bool QUdpSocketMock::bind ( const QHostAddress & address, quint16 port)
{
    Q_UNUSED(address);
    Q_UNUSED(port);
    return true;
}
