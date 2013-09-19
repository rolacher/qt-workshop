
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

    application.connect(&w, SIGNAL(request_quit()), SLOT(quit()));

    w.show();
    return application.exec();
}

} // IM
