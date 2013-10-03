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
    src/QPMockUpdateDelegate.cpp \
    src/QPMockBehaviorFactory.cpp \
    src/QPMockFactory.cpp \
    src/IMockDevice.cpp \
    src/UnattachedMockDevice.cpp \
    src/QPMockHandle.cpp

HEADERS +=\
        qphidget-mock_global.h \
    src/QPMockDevice.h \
    src/QPMock888Device.h \
    src/QPMock.h \
    src/phidget21.h \
    src/QPMockBehavior.h \
    src/QPMockUpdateContext.h \
    src/QPMockDataBehavior.h \
    src/QPMockUpdateDelegate.h \
    src/QPMockBehaviorFactory.h \
    src/QPMockFactory.h \
    src/IMockDevice.h \
    src/phidget21_types.h \
    src/UnattachedMockDevice.h \
    src/QPMockHandle.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

#QPhidget library will be rebuilt from sources linked against the test mock library

INCLUDEPATH += $$PWD/../qphidget-lib/src
HEADERS += $$PWD/../qphidget-lib/src/*.h
SOURCES += $$PWD/../qphidget-lib/src/*.cpp
