#ifndef APPLICATION_H
#define APPLICATION_H

#include <QtCore/QObject>

namespace IM {

class Application
{
public:
    Application();

    int execute(int argc, char * argv[]);
};

} // IM

#endif // APPLICATION_H
