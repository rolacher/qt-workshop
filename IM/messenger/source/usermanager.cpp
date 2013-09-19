#include "messenger/usermanager.h"

namespace IM {


UserManager::UserManager()
    : _pTimer(new QTimer(this)){

    connect(_pTimer, SIGNAL(timeout()), this, SLOT(checkIfUserLost()));
    _pTimer->start(TIMEOUT);
}

UserManager::~UserManager(){
    _pTimer->stop();
    delete _pTimer;
}

QStringList UserManager::getActiveUsers(){

    QStringList activeUsers;
    foreach(QString user, _usermap.keys()){
        activeUsers << user;
    }

    return activeUsers;
}

void UserManager::received_message(QString const & nickname) {
    addUser(nickname);
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

QStringList UserManager::getStaleUsers(const quint16 timeout) {

    QStringList staleTimestamps;
    QMap<QString,QDateTime>::Iterator it;

    for (it = _usermap.begin(); it != _usermap.end(); it++) {
        if (it.value().addSecs(timeout) < QDateTime::currentDateTime()) {
            staleTimestamps.append(it.key());
        }
    }

    return staleTimestamps;
}

void UserManager::checkIfUserLost(const quint16 timeout) {

    QStringList staleUsers = getStaleUsers(timeout);

    foreach(QString user, staleUsers) {
        removeUser(user);
    }
}

} // namespace IM
