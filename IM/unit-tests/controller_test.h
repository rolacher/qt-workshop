#ifndef CONTROLLER_TEST_H
#define CONTROLLER_TEST_H

#include <QtCore/QObject>

class ControllerTest : public QObject
{
    Q_OBJECT

private slots:
    void invoke_send_message_signals_send_the_message();
    //void wait_longer_than_timeout_sec_and_test_if_keep_alive_is_sent();
};

#endif // CONTROLLER_TEST_H
