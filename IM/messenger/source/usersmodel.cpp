#include "messenger/usersmodel.h"
#include "messenger/usermanager.h"

namespace IM {

UsersModel::UsersModel(QObject *parent, UserManager* user_manager) :
    QAbstractItemModel(parent),
    _pUserManager(user_manager)
{
}

void UsersModel::handle_user_list_changed()
{
    if (_pUserManager!=NULL)
    {
        beginRemoveColumns(QModelIndex(), 0, active_users.size());
        active_users.clear();
        endRemoveRows();

        QStringList newUsers = _pUserManager->getActiveUsers();
        beginInsertRows(QModelIndex(), 0, newUsers.size()-1);
        active_users.append(newUsers);
        endInsertRows();

        emit dataChanged(createIndex(0, 0), createIndex(active_users.size()-1, 0));
    }
}


QVariant UsersModel::data(const QModelIndex& index, int role) const
{
    if (index.row() >= active_users.size()) return QVariant();
    QString item = active_users.at(index.row());

    switch(role)
    {
        // qt specific roles
        case  Qt::DisplayRole:
            return item;
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
        return active_users.size();
    }
    return 0;
}

int UsersModel::columnCount(const QModelIndex& index) const
{
    Q_UNUSED(index);
    return 1;
}

}

