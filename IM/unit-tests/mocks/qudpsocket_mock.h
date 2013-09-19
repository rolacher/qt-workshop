#ifndef QUDPSOCKET_MOCK_H
#define QUDPSOCKET_MOCK_H

#include <QtCore/QObject>
#include <QtNetwork/QHostAddress>

#include "messenger/iudp_socket.h"

class QUdpSocketMock : public QObject, public IM::IUdpSocket
{
    Q_OBJECT

public:
    qint64 writeDatagram(QByteArray const & datagram, QHostAddress const & host, quint16 port);
    qint64 readDatagram(QByteArray const & datagram, qint64 maxsize, QHostAddress const & host, quint16 port);

signals:
    void called_writeDatagram(QByteArray const & datagram, QHostAddress const & host, quint16 port);
    void called_readDatagram(QByteArray const & datagram, qint64 maxsize, QHostAddress const & host, quint16 port);
};

Q_DECLARE_METATYPE(QHostAddress);

#endif // QUDPSOCKET_MOCK_H
