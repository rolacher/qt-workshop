#ifndef USERSMODEL_H
#define USERSMODEL_H

#include <QAbstractItemModel>
#include <QStringList>
#include "messenger/useritem.h"

namespace IM {

class UserManager;

class UsersModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit UsersModel(QObject *parent = 0, UserManager* user_manager=0);
    
signals:
    
public slots:
    void handle_user_list_changed();

private:
    UserManager* _pUserManager;
    QStringList active_users;

public:

    // return data as variant. Role selects image or text
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    // return empty index for flat structures. (special behavior needed for tree views)
    virtual QModelIndex parent(const QModelIndex& index) const;

    // create and return a standard index. (special behavior needed for tree views)
    virtual QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;

    // return row count. (here size of the list)
    virtual int rowCount(const QModelIndex& parent) const;

    // return columns. (here only 1)
    virtual int columnCount(const QModelIndex& index) const;
};

}

#endif // USERSMODEL_H
