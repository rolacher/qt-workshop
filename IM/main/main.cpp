#include <QtCore/QObject>

#include <messenger/application.h>

int main(int argc, char * argv[])
{
    IM::Application application;
    return application.execute(argc, argv);
}
