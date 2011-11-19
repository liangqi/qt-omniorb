CONFIG       += debug
HEADERS       = omniorbthread.h ../echo_callback.h
SOURCES       = main.cpp omniorbthread.cpp ../echo_callback.cpp
!win32:LIBS += -lomniORB4 -lomnithread -lssl -lcrypto
