#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

#include "omniorbthread.h"

class QPushButton;
class QTextEdit;
class QString;
class QSpinBox;

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(int argc, char **argv);

public slots:
    void startThread();
    void onceThread();
    void shutdownThread();
    void textChanged( const QString & );

    void threadOver();

protected:
    int _argc;
    char **_argv;

private:
    OmniORBThread *thread;
    QTextEdit *editor;
    QPushButton *start;
    QPushButton *once;
    QPushButton *shutdown;
    QSpinBox *period;
    QSpinBox *timeout;
    QString text;
    int i;
};

#endif
