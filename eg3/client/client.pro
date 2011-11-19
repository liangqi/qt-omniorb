CONFIG       += debug
HEADERS       = omniorbthread.h ../echo.h
SOURCES       = main.cpp omniorbthread.cpp ../echo.cpp
!win32:LIBS += -lomniORB4 -lomnithread -lssl -lcrypto
