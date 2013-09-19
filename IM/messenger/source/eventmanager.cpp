#include "include/messenger/eventmanager.h"

namespace IM {

EventManager::EventManager()
    : _pTimer(new QTimer(this)) {

    connect(_pTimer, SIGNAL(timeout()), this, SLOT(checkIfEventCanceled()));
    _pTimer->start(TIMEOUT);
}

EventManager::~EventManager()
{
    _pTimer->stop();
    delete _pTimer;
}

QStringList EventManager::getActiveEvents()
{
    QStringList activeEvents;
    foreach(QString event, _eventMap.keys()){
        activeEvents << event;
    }

    return activeEvents;
}

void EventManager::addEvent(QString event)
{
    bool eventListChanged = !_eventMap.contains(event);

    _eventMap.insert(event,QDateTime::currentDateTime());

    if (eventListChanged) {
       emit EventListChanged();
    }
}

void EventManager::removeEvent(QString event)
{
    bool eventListChanged = _eventMap.contains(event);


   _eventMap.remove(event);

    if (eventListChanged) {
       emit EventListChanged();
    }
}


QStringList EventManager::getActiveUsersFromEvent(QString event)
{
    //TODO
    return QStringList();
}

void EventManager::addUserToEvent(QString event, QString user)
{
//TODO
}

void EventManager::removeUserFromEvent(QString event, QString user)
{
//TODO
}

QStringList EventManager::getStaleEvents(const quint16 timeout) {
    QStringList staleTimestamps;
    QMap<QString,QDateTime>::Iterator it;

    for (it = _eventMap.begin(); it != _eventMap.end(); it++) {
        if (it.value().addSecs(timeout) < QDateTime::currentDateTime()) {
            staleTimestamps.append(it.key());
        }
    }

    return staleTimestamps;
}


void EventManager::checkIfEventCanceled(const quint16 timeout)
{

    QStringList staleEvents = getStaleEvents(timeout);

    foreach(QString event, staleEvents) {
        removeEvent(event);
    }
}


void EventManager::checkIfUserUnsubscribedEvent(const quint16 timeout)
{
//TODO
}

void EventManager::received_event(QString const & event)
{
    addEvent(event);
}

void EventManager::received_userParticipatesEvent(QString const & event, QString const & user)
{
    addUserToEvent(event, user);
}

} // namespace IM
