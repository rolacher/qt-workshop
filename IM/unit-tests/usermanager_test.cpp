#include "usermanager_test.h"
#include "messenger/usermanager.h"

#include <QtTest/QTest>
#include <QtTest/QSignalSpy>
#include <QStringList>

UserManagerTest::UserManagerTest(QObject *parent) :
    QObject(parent)
{
}



void UserManagerTest::checkEmptyUserListOnCreation(){

    UserManager testee;
    QVERIFY(testee.getActiveUsers().isEmpty());

}

void UserManagerTest::checkAddUserUpdatesCheckUserList(){

    const QString expectedUser("Bart Simpson");
    UserManager testee;

    testee.addUser(expectedUser);
    QVERIFY(!testee.getActiveUsers().isEmpty());
    QVERIFY(-1 < testee.getActiveUsers().indexOf(expectedUser));
}

void UserManagerTest::checkRemoveUserUpdatesCheckUserList(){
    const QString expectedUser("Marge Simpson");
    UserManager testee;

    testee.addUser(expectedUser);
    testee.removeUser(expectedUser);
    QVERIFY(testee.getActiveUsers().isEmpty());
    QVERIFY(-1 == testee.getActiveUsers().indexOf(expectedUser));
}

void UserManagerTest::checkAddUserSendsUserListUpdatedSignal(){

    const QString expectedUser("Bart Simpson");
    UserManager testee;
    QSignalSpy signal_spy(&testee, SIGNAL(UserListChanged()));

    testee.addUser(expectedUser);

    QVERIFY(1 == signal_spy.count());
}

void UserManagerTest::checkRemoveUserSendsUserListUpdatedSignal(){

    const QString expectedUser("Bart Simpson");
    UserManager testee;

    testee.addUser(expectedUser);


    QSignalSpy signal_spy(&testee, SIGNAL(UserListChanged()));
    testee.removeUser(expectedUser);
    QVERIFY(1 == signal_spy.count());
}
