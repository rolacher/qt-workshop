#ifndef IUDP_SOCKET_H
#define IUDP_SOCKET_H

#include <QtCore/QtGlobal>
#include <QObject>

class QHostAddress;
class QByteArray;

namespace IM {

class IUdpSocket :
    public QObject
{
    Q_OBJECT
public:
    IUdpSocket(QObject* parent = NULL): QObject(parent){};

    virtual qint64 writeDatagram(QByteArray const & datagram, QHostAddress const & host, quint16 port) = 0;
    virtual bool bind ( const QHostAddress & address, quint16 port) = 0;

signals:
    void datagramReceived(QByteArray& array);
};

} // IM
#endif // IUDP_SOCKET_H
