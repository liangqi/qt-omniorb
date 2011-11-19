CONFIG       += debug
HEADERS       = mainwidget.h ../echo.h
SOURCES       = main.cpp mainwidget.cpp ../echo.cpp
!win32:LIBS += -lomniORB4 -lomnithread -lssl -lcrypto
