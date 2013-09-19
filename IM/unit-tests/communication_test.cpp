#include <QtTest/QTest>
#include <QtTest/QSignalSpy>

#include <messenger/communication.h>

#include "mocks/qudpsocket_mock.h"
#include "communication_test.h"

void CommunicationTest::handle_send_message_broadcasts_the_message_over_udp()
{
    // arrange
    qRegisterMetaType<QHostAddress>("QHostAddress");
    QUdpSocketMock udp_socket;
    QSignalSpy writeDatagram(&udp_socket, SIGNAL(called_writeDatagram(QByteArray const &, QHostAddress const &, quint16)));

    // act
    IM::Communication testee(udp_socket);
    const QString expected_nickname = "Name";
    const QString expected_message = "Hello world.";
    testee.handle_send_message(expected_nickname, expected_message);

    // assert
    QCOMPARE(writeDatagram.count(), 1);

    const auto arguments = writeDatagram.takeFirst();
    QDataStream data(arguments.at(0).toByteArray());

    quint32 command;
    QString nickname;
    QString message;
    data >> command >> nickname >> message;

    const quint32 expected_command = IM::Command::Message;
    QCOMPARE(command, expected_command);
    QCOMPARE(nickname, expected_nickname);
    QCOMPARE(message, expected_message);

    const QHostAddress expected_address = QHostAddress::Broadcast;
    QCOMPARE(qvariant_cast<QHostAddress>(arguments.at(1)), expected_address);

    const quint32 expected_port = 41000;
    QCOMPARE(arguments.at(2).toUInt(), expected_port);


}

void CommunicationTest::handle_receive_message_over_udp()
{
    // arrange
    qRegisterMetaType<QHostAddress>("QHostAddress");
    QUdpSocketMock udp_socket;
    IM::Communication testee(udp_socket);
    QSignalSpy receivedMessage(&testee, SIGNAL(received_message(QString const &, QString const &)));

    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_5_0);

    const QString expected_nickname = "Name";
    const QString expected_message = "Hello world.";
    stream << IM::Command::Message;
    stream << expected_nickname;
    stream << expected_message;


    // act
    testee.handle_receive_message(data);

    // assert
    QCOMPARE(receivedMessage.count(), 1);

    const auto arguments = receivedMessage.takeFirst();
    QCOMPARE(arguments.at(0).toString(), expected_nickname);
    QCOMPARE(arguments.at(1).toString(), expected_message);
}
