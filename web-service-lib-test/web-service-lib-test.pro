#-------------------------------------------------
#
# Project created by QtCreator 2013-10-06T11:32:24
#
#-------------------------------------------------

QT       += network testlib

QT       -= gui

TARGET = tst_webService
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    main.cpp \
    tst_HttpDaemon.cpp \
    tst_WebAppControllerTest.cpp

HEADERS += \
    tst_HttpDaemon.h \
    tst_WebAppControllerTest.h

DEFINES += SRCDIR=\\\"$$PWD/\\\"

# web-service-lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../hvac-service-lib/ -lhvac-service-lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../hvac-service-lib/ -lhvac-service-libd
else:unix: LIBS += -L$$PWD/../hvac-service-lib/ -lhvac-service-lib

INCLUDEPATH += $$PWD/../hvac-service-lib
DEPENDPATH += $$PWD/../hvac-service-lib
