#ifndef USERMANAGER_TEST_H
#define USERMANAGER_TEST_H

#include <QObject>

class UserManagerTest : public QObject
{
    Q_OBJECT
public:
    explicit UserManagerTest(QObject *parent = 0);

signals:

private slots:

    void checkEmptyUserListOnCreation();
    void checkAddUserUpdatesCheckUserList();
    void checkRemoveUserUpdatesCheckUserList();

};

#endif // USERMANAGER_TEST_H
