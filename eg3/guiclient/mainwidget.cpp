#include <QtGui>

#include "mainwidget.h"

MainWidget::MainWidget(int argc, char **argv)
    : _argc(argc), _argv(argv), text(), i(0)
{
  button = new QPushButton( "ECHO" );
  editor = new QTextEdit;

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(editor);
  mainLayout->addWidget(button);
  setLayout(mainLayout);

  thread = new OmniORBThread( _argc, _argv, this );
  QObject::connect( thread, SIGNAL( textChanged( const QString& ) ), this, SLOT( textChanged( const QString& ) ) );

  connect( button, SIGNAL( clicked() ), this, SLOT( echoThread() ) );
}

void MainWidget::echoThread()
{
    i = 0;
    text = "";
    editor->setText( text );

    thread->start();
}

void MainWidget::textChanged( const QString &str )
{
    text += QString( "\n%1 \n%2" ).arg( i ).arg( str );
    i += 1;
    editor->setText( text );
}
