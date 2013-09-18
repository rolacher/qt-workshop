#include <messenger/nickname.h>
#include <QFile>
#include <QDataStream>

namespace IM
{

static const QString DEFAULT="DEFINE NICKNAME";

NickName::NickName(const QString& path, QObject* parent) :
    QObject(parent),
    _filename(path),
    _initialized(false)
{
    _nickname = DEFAULT;
}

const QString& NickName::getNickname()
{
    if (!_initialized)
    {
        load();
        _initialized=false;
    }
    return _nickname;
}

void NickName::setNickname(const QString& name)
{
    _nickname = name;
    save();
}

void NickName::save()
{
    QFile save_file(_filename);
    save_file.open(QIODevice::WriteOnly);
    QDataStream out(&save_file);
    out << _nickname;
    save_file.close();
}

void NickName::load()
{
    QFile load_file(_filename);
    if (load_file.open(QIODevice::ReadOnly))
    {
        QDataStream in(&load_file);
        in >> _nickname;
    }
    load_file.close();
}

}
