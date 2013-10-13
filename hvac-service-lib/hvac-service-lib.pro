#-------------------------------------------------
#
# Project created by QtCreator 2013-10-06T10:00:05
#
#-------------------------------------------------

QT       += network serviceframework

QT       -= gui

TARGET = hvac-service-lib
TEMPLATE = lib

DEFINES += HVACSERVICELIB_LIBRARY

SOURCES += HvacServiceLib.cpp \
    HttpDaemon.cpp \
    HvacZone.cpp \
    WebAppController.cpp \
    WebAppUriHandler.cpp \
    WebAppRequest.cpp \
    WebAppResponse.cpp

HEADERS += HvacServiceLib.h\
        hvac-service-lib_global.h \
    HttpDaemon.h \
    HvacZone.h \
    WebAppController.h \
    WebAppUriHandler.h \
    WebAppRequest.h \
    WebAppResponse.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
