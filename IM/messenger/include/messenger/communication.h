#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QtCore/QObject>

namespace IM {

class IUdpSocket;

class Command {
public:
    static quint32 const KeepAlive;
    static quint32 const Message;
};

class Communication : public QObject
{
    Q_OBJECT
public:
    Communication(IUdpSocket & udp_socket);

public slots:
    void handle_send_message(QString const & nickname, QString const & message);
    void handle_receive_message(QByteArray & data);

signals:
    void received_message(QString const & nickname, QString const & message);

private:
    IUdpSocket & _udp_socket;
    quint16 _port;
};

} // IM

#endif // COMMUNICATION_H
