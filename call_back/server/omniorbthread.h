#ifndef OMNIORBTHREAD_H
#define OMNIORBTHREAD_H

#include <QThread>

class OmniORBThread : public QThread
{
    Q_OBJECT

public:
    OmniORBThread(int argc, char **argv, QObject *parent = 0);
    ~OmniORBThread();

protected:
    void run();
    int _argc;
    char **_argv;
};

#endif
