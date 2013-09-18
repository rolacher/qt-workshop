#ifndef NICKNAME_H
#define NICKNAME_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QDateTime>
#include <QStringList>
#include <QTimer>


namespace IM
{

class NickName :
    public QObject
{
public:
    NickName(const QString& path, QObject* parent = NULL);
    const QString& getNickname();
    void setNickname(const QString& name);

    void save();
    void load();

   private:
    QString _nickname;
    QString _filename;

    bool _initialized;
};

};
#endif
