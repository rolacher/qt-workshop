#ifndef UDP_SOCKET_H
#define UDP_SOCKET_H

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include "messenger/iudp_socket.h"

namespace IM {

class UdpSocket :
        public IUdpSocket
{
    Q_OBJECT
public:
    UdpSocket(QObject* parent = NULL);
    virtual qint64 writeDatagram(QByteArray const & datagram, QHostAddress const & host, quint16 port) override final;

    // TODO signal -> itf must inherit QObject
    //QUdpSocket& getSocket();

    //signals:
    //void datagramReceived(const QByteArray& array);

    virtual bool bind ( const QHostAddress & address, quint16 port);


private slots:
    void readPendingDatagrams();

private:
    QUdpSocket _udp_socket;
};

} // IM

#endif // UDP_SOCKET_H
