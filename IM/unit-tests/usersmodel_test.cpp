#include <QtTest/QTest>
#include <QtTest/QSignalSpy>

#include <messenger/usersmodel.h>

#include "usersmodel_test.h"

void UserModelTest::handle_empty_list_consistency()
{
    UsersModel modelUnderTest;

    QModelIndex index_at_0_0 = modelUnderTest.index(0, 0);
    QVariant data_at_0_0 = modelUnderTest.data(index_at_0_0);
    QCOMPARE(data_at_0_0.isValid(), false);
}

// TODO: add a lot more tests
