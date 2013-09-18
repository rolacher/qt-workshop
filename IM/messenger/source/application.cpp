
#include <QApplication>

#include "messenger/application.h"
#include "messenger/mainwindow.h"


namespace IM
{

Application::Application()
{
}

int Application::execute(int argc, char * argv[])
{
    QApplication application(argc, argv);
    MainWindow w;
    w.show();
    return application.exec();
}

} // IM
