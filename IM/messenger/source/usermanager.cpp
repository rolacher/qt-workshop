#include "messenger/usermanager.h"

UserManager::UserManager(){

}

UserManager::~UserManager(){

}

QStringList UserManager::getActiveUsers(){

    QStringList activeUsers;
    foreach(QString user, _usermap.keys()){
        activeUsers << user;
    }

    return activeUsers;
}

void UserManager::addUser(QString user){
    _usermap.insert(user,QDateTime::currentDateTime());
}

void UserManager::removeUser(QString user){
    _usermap.remove(user);
}
