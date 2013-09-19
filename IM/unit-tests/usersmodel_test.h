#ifndef USERMODELTEST_H
#define USERMODELTEST_H

#include <QObject>

class UserModelTest : public QObject
{
    Q_OBJECT

private slots:
    void handle_empty_list_consistency();
};

#endif // USERMODELTEST_H
