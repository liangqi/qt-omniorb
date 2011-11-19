#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

#include "omniorbthread.h"

class QPushButton;
class QTextEdit;
class QString;

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(int argc, char **argv);

public slots:
    void echoThread();
    void textChanged( const QString & );

protected:
    int _argc;
    char **_argv;

private:
    OmniORBThread *thread;
    QTextEdit *editor;
    QPushButton *button;
    QString text;
    int i;
};

#endif
