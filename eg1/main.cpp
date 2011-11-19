#include "omniorbthread.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    OmniORBThread thread( argc, argv, &app );
    thread.start();
    QObject::connect( &thread, SIGNAL(finished()), &app, SLOT(quit()) );
    return app.exec();
}
