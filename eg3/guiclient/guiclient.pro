CONFIG       += debug
QT           += widgets
HEADERS       = mainwidget.h omniorbthread.h ../echo.h
SOURCES       = main.cpp mainwidget.cpp omniorbthread.cpp ../echo.cpp
!win32:LIBS += -lomniORB4 -lomnithread -lssl -lcrypto
