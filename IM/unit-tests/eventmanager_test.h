#ifndef EVENTMANAGER_TEST_H
#define EVENTMANAGER_TEST_H

#include <QObject>

class EventManagerTest : public QObject
{
    Q_OBJECT
public:
    explicit EventManagerTest(QObject *parent = 0);

signals:

private slots:

    void checkEmptyEventListOnCreation();
    void checkReceivedEventUpdatesEventList();
    void checkRemoveEventUpdatesEventUserList();
    void checkReceivedEventTriggersUpdatedSignal();
    void checkRemoveEventTriggersUpdatedSignal();
    void checkIfcheckIfEventCanceledRemovesEvent();
};

#endif // EVENTMANAGER_TEST_H
