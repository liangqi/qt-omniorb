#ifndef OMNIORBTHREAD_H
#define OMNIORBTHREAD_H

#include <QThread>
#include <QString>

#include "../echo.h"

class OmniORBThread : public QThread
{
    Q_OBJECT

public:
    OmniORBThread(int argc, char **argv, QObject *parent = 0);
    ~OmniORBThread();

signals:
    void textChanged( const QString &str );

protected:
    void run();
    int _argc;
    char **_argv;

private:
    void hello(Echo_ptr e);
};

#endif
