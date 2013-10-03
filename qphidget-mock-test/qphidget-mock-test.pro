#-------------------------------------------------
#
# Project created by QtCreator 2013-09-15T06:17:40
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_QPhidgetMockTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_QPhidgetMockTest.cpp \
    QPTestBehavior.cpp

HEADERS += \
    QPTestBehavior.h

DEFINES += SRCDIR=\\\"$$PWD/\\\"

# qphidget-mock

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../qphidget-mock/ -lqphidget-mock
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../qphidget-mock/ -lqphidget-mockd
else:unix: LIBS += -L$$PWD/../qphidget-mock/ -lqphidget-mock

INCLUDEPATH += $$PWD/../qphidget-mock/src\
    $$PWD/../qphidget-lib/src
DEPENDPATH += $$PWD/../qphidget-mock

