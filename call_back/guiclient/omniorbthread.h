#ifndef OMNIORBTHREAD_H
#define OMNIORBTHREAD_H

#include <QThread>
#include <QString>
#include <QMutex>

#include "../echo_callback.h"

class OmniORBThread : public QThread
{
    Q_OBJECT

public:
    OmniORBThread(int argc, char **argv, QObject *parent = 0);
    ~OmniORBThread();

signals:
    void textChanged( const QString &str );

public slots:
    void slotTextChanged( const QString &str );

public:
    void setType( int v ) { type = v; }
    void setPeriod( int v ) { p = v; }
    void setTimeout( int v ) { to = v; }

private:
    void do_single(cb::Server_ptr server, cb::CallBack_ptr cb);
    void do_register(cb::Server_ptr server, cb::CallBack_ptr cb,
	             int period, int time_to_shutdown);

protected:
    void run();
    int _argc;
    char **_argv;

    int type;
    int p;
    int to;
};

#endif
