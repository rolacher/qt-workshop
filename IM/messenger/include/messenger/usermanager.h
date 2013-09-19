#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QDateTime>
#include <QStringList>

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


signals:
   void UserListChanged(void);


private:

    QMap<QString,QDateTime> _usermap;

};

#endif // USERMANAGER_H
