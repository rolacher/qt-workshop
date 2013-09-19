#include "messenger/usersmodel.h"

UsersModel::UsersModel(QObject *parent) :
    QAbstractItemModel(parent)
{
}

void UsersModel::addUser(const QString& nick)
{
    foreach (UserItem* user, _registeredUsers)
    {
       if (user->_nickname==nick) return;
    }

    UserItem* item = new UserItem(nick);
    _registeredUsers.append(item);
}

void UsersModel::removeUser(const QString & nick)
{
    for (QList<UserItem*>::Iterator iter = _registeredUsers.begin();
         iter != _registeredUsers.end();
         ++iter)
    {
        if ((*iter)->_nickname==nick) {
            _registeredUsers.erase(iter);
        }
    }
}


QVariant UsersModel::data(const QModelIndex& index, int role) const
{
    if (index.row() >= _registeredUsers.size()) return QVariant();
    UserItem* item = _registeredUsers.at(index.row());
    if (!item) return QVariant();

    switch(role)
    {
        // qt specific roles
        case  Qt::DisplayRole:
            return item->_nickname;
        break;

        //case Qt::DecorationRole:
        //    return item->_nickname;
        //break;

        default:
            return QVariant();
    }
    return QVariant();
}

QModelIndex UsersModel::parent(const QModelIndex& index) const
{
    Q_UNUSED(index);
    return QModelIndex();
}

QModelIndex UsersModel::index(int row, int column, const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return createIndex(row, column);
}

int UsersModel::rowCount(const QModelIndex& parent) const
{
    if (!parent.isValid())
    {
        return _registeredUsers.size();
    }
    return 0;
}

int UsersModel::columnCount(const QModelIndex& index) const
{
    Q_UNUSED(index);
    return 1;
}


