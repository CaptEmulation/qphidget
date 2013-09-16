#-------------------------------------------------
#
# Project created by QtCreator 2013-09-14T22:10:01
#
#-------------------------------------------------

QT       -= gui

TARGET = qphidget-mock
TEMPLATE = lib

DEFINES += QPHIDGETMOCK_LIBRARY

INCLUDEPATH += src

SOURCES += \
    src/phidget21.cpp \
    src/QPMockDevice.cpp \
    src/QPMock888Device.cpp \
    src/QPMock.cpp \
    src/QPMockBehavior.cpp \
    src/QPMockUpdateContext.cpp \
    src/QPMockDataBehavior.cpp \
    src/QPMockUpdateDelegate.cpp

HEADERS +=\
        qphidget-mock_global.h \
    src/QPMockDevice.h \
    src/QPMock888Device.h \
    src/QPMock.h \
    src/phidget21.h \
    src/QPMockBehavior.h \
    src/QPMockUpdateContext.h \
    src/QPMockDataBehavior.h \
    src/QPMockUpdateDelegate.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

# qphidget-lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../qphidget-lib/ -lqphidget-lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../qphidget-lib/ -lqphidget-libd
else:unix: LIBS += -L$$PWD/../qphidget-lib/ -lqphidget-lib

INCLUDEPATH += $$PWD/../qphidget-lib
DEPENDPATH += $$PWD/../qphidget-lib
