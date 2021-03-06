#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>



namespace Ui {
class MainWindow;
}

namespace IM
{
class Controller;
class Communication;
class UdpSocket;
class UserManager;
class UsersModel;
class EventManager;
class NickName;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void set_nickname(const QString & nickname);

signals:
    void send_message(QString const & message);
    void request_quit();

public slots:
    void handleIncommingMessage(const QString& from_nickname, const QString& message);

private slots:
    void handleSendMessage();
    void editClicked();

private:
    void updateNickName();

private:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    static const QString _persistFilename;

    Controller* _pController;
    Communication* _pCommunication;
    UserManager* _pUserManager;
    UsersModel* _pUsersModel;
    EventManager* _pEventManager;
    UdpSocket* _pUdpSocket;
    NickName* _nickName;
    Ui::MainWindow *ui;

};

} // IM

#endif // MAINWINDOW_H
