#-------------------------------------------------
#
# Project created by QtCreator 2013-08-18T02:54:19
#
#-------------------------------------------------


###########################
###    SETUP OUTPUT     ###
###########################

DEBUG_TARGET = qphidgetd
RELEASE_TARGET = qphidget
OUTDIR = ..

CONFIG(debug, debug|release){
    TARGET = $$DEBUG_TARGET
}

CONFIG(release, debug|release){
    TARGET = $$RELEASE_TARGET
    DEFINES += QT_NO_DEBUG_OUTPUT
}

DESTDIR = $$OUTDIR/lib/$$RELEASE_TARGET

# QT Options

QT       -= gui

TARGET = qphidget-lib
TEMPLATE = lib

CONFIG(debug) {
    CONFIG += staticlib
}

# Dependencies


# Phidget library settings

unix: LIBS += -lphidget21

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



###########################
###       INSTALL       ###
###########################

OUTINCLUDE = $$PWD/../include

win32 {
    OUTINCLUDE ~= s,/,\\,g
    QMAKE_POST_LINK += $$quote(if not exist $$OUTINCLUDE\\$$RELEASE_TARGET mkdir $$OUTINCLUDE\\$$RELEASE_TARGET)

    for(header, HEADERS) {
        header ~= s,/,\\,g
        QMAKE_POST_LINK += $$quote(xcopy $$header $$OUTINCLUDE\\$$RELEASE_TARGET /y)
    }
}

unix {
    QMAKE_POST_LINK += $$quote(mkdir -p $$OUTINCLUDE/$$RELEASE_TARGET$$escape_expand(\\n\\t))

    for(header, HEADERS) {
       QMAKE_POST_LINK += $$quote(cp -u $$header $$OUTINCLUDE/$$RELEASE_TARGET$$escape_expand(\\n\\t))
    }
}
