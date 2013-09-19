#include "eventmanager_test.h"
#include "messenger/eventmanager.h"

#include <QtTest/QTest>
#include <QtTest/QSignalSpy>
#include <QStringList>


EventManagerTest::EventManagerTest(QObject *parent) :
    QObject(parent)
{
}



void EventManagerTest::checkEmptyEventListOnCreation(){

    IM::EventManager testee;
    QVERIFY(testee.getActiveEvents().isEmpty());
}


void EventManagerTest::checkReceivedEventUpdatesEventList() {
    QString expectedEventName = "bbv Geburtstagsparty";
    IM::EventManager testee;

    testee.received_event(expectedEventName);

    QVERIFY(!testee.getActiveEvents().isEmpty());
    QVERIFY(-1 < testee.getActiveEvents().indexOf(expectedEventName));
}


void EventManagerTest::checkRemoveEventUpdatesEventUserList(){
    QString expectedEventName = "bbv Geburtstagsparty";
    IM::EventManager testee;

    testee.received_event(expectedEventName);
    testee.removeEvent(expectedEventName);

    QVERIFY(testee.getActiveEvents().isEmpty());
    QVERIFY(-1 == testee.getActiveEvents().indexOf(expectedEventName));

}


void EventManagerTest::checkReceivedEventTriggersUpdatedSignal(){

    QString expectedEventName = "bbv Geburtstagsparty";
    IM::EventManager testee;
    QSignalSpy signal_spy(&testee, SIGNAL(EventListChanged()));

    testee.received_event(expectedEventName);

    QVERIFY(1 == signal_spy.count());
}


void EventManagerTest::checkRemoveEventTriggersUpdatedSignal(){
    QString expectedEventName = "bbv Geburtstagsparty";
    IM::EventManager testee;

    testee.received_event(expectedEventName);

    QSignalSpy signal_spy(&testee, SIGNAL(EventListChanged()));
    testee.removeEvent(expectedEventName);
    QVERIFY(1 == signal_spy.count());

}


void EventManagerTest::checkIfcheckIfEventCanceledRemovesEvent() {
    QString expectedEventName = "bbv Geburtstagsparty";
    IM::EventManager testee;

    testee.received_event(expectedEventName);
    QTest::qSleep (1200);

    testee.checkIfEventCanceled(1);   // "simulate" time trigger
    QVERIFY(testee.getActiveEvents().isEmpty());
    QVERIFY(-1 == testee.getActiveEvents().indexOf(expectedEventName));
}
