#-------------------------------------------------
#
# Project created by QtCreator 2013-08-18T02:54:19
#
#-------------------------------------------------


# QT Options

QT       -= gui

TARGET = qphidget-lib
TEMPLATE = lib

CONFIG(debug) {
    CONFIG += staticlib
}

# Dependencies


# Phidget library settings

macx:unix {
    LIBS += phidget21
}

win32 {
    win32:LIBS += "C:/Program Files/Phidgets/phidget21.lib"
    INCLUDEPATH += "C:/Program Files/Phidgets"
    HEADERS += "C:/Program Files/Phidgets/phidget21.h"
}


# Source settings

DEFINES += QPHIDGETLIB_LIBRARY

INCLUDEPATH += src

SOURCES += \
    src/QPInterfaceKitFactory.cpp \
    src/QP888Device.cpp \
    src/QPManager.cpp \
    src/QPDigitalIO.cpp

HEADERS += \
    qphidget-lib_global.h \
    src/QP888Device.h \
    src/QPManager.h \
    src/QPDigitalIO.h \
    src/QPInterfaceKitFactory.h \
    qphidget.h


# Deployment operations

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
