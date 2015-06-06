#include <QtWidgets>

#include "mainwidget.h"

MainWidget::MainWidget(int argc, char **argv)
    : _argc(argc), _argv(argv), text(), i(0)
{
  once = new QPushButton( "ONCE" );
  start = new QPushButton( "START" );
  shutdown = new QPushButton( "SHUTDOWN" );

  QLabel *l1 = new QLabel( "Period:" );
  QLabel *l2 = new QLabel( "Timeout:" );

  period = new QSpinBox;
  period->setValue( 1 );
  period->setMinimum( 1 );
  period->setMaximum( 10 );

  timeout = new QSpinBox;
  timeout->setValue( 1 );
  timeout->setMinimum( 1 );
  timeout->setMaximum( 100 );

  editor = new QTextEdit;

  QHBoxLayout *h1 = new QHBoxLayout;
  h1->addWidget( l1 );
  h1->addWidget( period );

  QHBoxLayout *h2 = new QHBoxLayout;
  h2->addWidget( l2 );
  h2->addWidget( timeout );

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(editor);
  mainLayout->addLayout( h1 );
  mainLayout->addLayout( h2 );
  mainLayout->addWidget(start);
  mainLayout->addWidget(once);
  mainLayout->addWidget(shutdown);
  setLayout(mainLayout);

  thread = new OmniORBThread( _argc, _argv, this );
  QObject::connect( thread, SIGNAL( textChanged( const QString& ) ), this, SLOT( textChanged( const QString& ) ) );
  QObject::connect( thread, SIGNAL( finished() ), this, SLOT( threadOver() ) );

  connect( start, SIGNAL( clicked() ), this, SLOT( startThread() ) );
  connect( once, SIGNAL( clicked() ), this, SLOT( onceThread() ) );
  connect( shutdown, SIGNAL( clicked() ), this, SLOT( shutdownThread() ) );
}

void MainWidget::onceThread()
{
    once->setEnabled( false );

    i = 0;
    text = "once\n";
    editor->setText( text );

    thread->setType( 1 );

    thread->start();

    //once->setEnabled( true );
}

void MainWidget::startThread()
{
    start->setEnabled( false );

    i = 0;
    text = "start\n";
    editor->setText( text );

    int p = period->value();
    int t = timeout->value();
    if ( t < p ) {
      t = p;
      timeout->setValue( t );
    }

    thread->setType( 2 );
    thread->setPeriod( p );
    thread->setTimeout( t );

    thread->start();

    //start->setEnabled( true );
}

void MainWidget::shutdownThread()
{
    once->setEnabled( false );
    start->setEnabled( false );
    shutdown->setEnabled( false );

    i = 0;
    text = "shutdown\n";
    editor->setText( text );

    thread->setType( 0 );

    thread->start();

    //once->setEnabled( true );
}

void MainWidget::threadOver()
{
    shutdown->setEnabled( true );
    start->setEnabled( true );
    once->setEnabled( true );
}

void MainWidget::textChanged( const QString &str )
{
    text += QString( "\n%1 \n%2" ).arg( i ).arg( str );
    i += 1;
    editor->setText( text );
}
