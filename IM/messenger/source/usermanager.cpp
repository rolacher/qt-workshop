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
    bool userListChanged = !_usermap.contains(user);

    _usermap.insert(user,QDateTime::currentDateTime());

    if (userListChanged) {
        emit UserListChanged();
    }
}

void UserManager::removeUser(QString user){

    bool userListChanged = _usermap.contains(user);

    _usermap.remove(user);

    if (userListChanged) {
        emit UserListChanged();
    }
}
