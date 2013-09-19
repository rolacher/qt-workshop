#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QDateTime>
#include <QStringList>
#include <QTimer>


namespace IM {


class IUserManager
{
public:
    virtual QStringList getActiveUsers() = 0;

    virtual void addUser(QString user) =  0;
    virtual void removeUser(QString user) = 0;
};

class UserManager : public QObject, public  IUserManager
{
    Q_OBJECT

public:

    UserManager();
    ~UserManager();

    QStringList getActiveUsers();

    void addUser(QString user);
    void removeUser(QString user);

public slots:
    void checkIfUserLost(const quint16 timeout = 7);
    void received_message(QString const & nickname);


signals:
   void UserListChanged(void);


private:

   QStringList getStaleUsers(const quint16 timeout);

   QMap<QString,QDateTime> _usermap;

   QTimer* _pTimer;

   static const quint16 TIMEOUT = 7;

};

} // namespace IM

#endif // USERMANAGER_H
