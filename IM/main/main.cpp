#include <QtCore/QObject>

#include <messenger/application.h>

int main(int argc, char * argv[])
{
    Q_INIT_RESOURCE(emoticons);
    IM::Application application;
    return application.execute(argc, argv);
}
