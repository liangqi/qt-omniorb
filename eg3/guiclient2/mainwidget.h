#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

#include "../echo.h"

class QPushButton;
class QTextEdit;
class QString;

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(int argc, char **argv);
    ~MainWidget();

public slots:
    void echoThread();
    void textChanged( const QString & );

protected:
    int _argc;
    char **_argv;

private:
    QTextEdit *editor;
    QPushButton *button;
    QString text;
    int i;

private:
    void hello(Echo_ptr e);
};

#endif
