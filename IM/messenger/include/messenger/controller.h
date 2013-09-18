#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

class QTimer;

namespace IM {

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller();

    void set_nickname(const QString & nickname);

signals:
    void send_message(const QString & nickname, QString const & message);
    void send_keepalive(const QString & nickname);

public slots:
    void handle_send_message(const QString & message);

private slots:
    void handle_timeout();

private:

    QString _nickname;
    QTimer* _pTimer;

    static const quint16 TIMEOUT = 5000;

};

} // IM

#endif // CONTROLLER_H
