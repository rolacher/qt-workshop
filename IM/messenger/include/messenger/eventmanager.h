#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QDateTime>
#include <QStringList>
#include <QTimer>


namespace IM {


class IEventManager
{
public:
    virtual QStringList getActiveEvents() = 0;
    virtual void addEvent(QString event) =  0;
    virtual void removeEvent(QString event) = 0;

    virtual QStringList getActiveUsersFromEvent(QString event) = 0;
    virtual void addUserToEvent(QString event, QString user) =  0;
    virtual void removeUserFromEvent(QString event, QString user) = 0;
};

class EventManager : public QObject, public  IEventManager
{
    Q_OBJECT

public:

    EventManager();
    ~EventManager();

    QStringList getActiveEvents();
    virtual void addEvent(QString event);
    virtual void removeEvent(QString event);

    virtual QStringList getActiveUsersFromEvent(QString event);
    virtual void addUserToEvent(QString event, QString user);
    virtual void removeUserFromEvent(QString event, QString user);

public slots:
    void checkIfEventCanceled(const quint16 timeout = 7);
    void checkIfUserUnsubscribedEvent(const quint16 timeout = 7);
    void received_event(QString const & event);
    void received_userParticipatesEvent(QString const & event, QString const & user);


signals:
   void EventListChanged(void);
   void EventParticipationListChanged(void);


private:

   QStringList getStaleEvents(const quint16 timeout);

   QMap<QString,QDateTime> _eventMap;

   QTimer* _pTimer;

   static const quint16 TIMEOUT = 7;

};

} // namespace IM

#endif // EVENTMANAGER_H

