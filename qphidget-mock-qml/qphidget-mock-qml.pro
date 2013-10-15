###########################
###    SETUP OUTPUT     ###
###########################

DEBUG_TARGET = qphidget-mock-qmld
RELEASE_TARGET = qphidget-mock-qml
OUTDIR = ..

CONFIG(debug, debug|release){
    TARGET = $$DEBUG_TARGET
}

CONFIG(release, debug|release){
    TARGET = $$RELEASE_TARGET
    DEFINES += QT_NO_DEBUG_OUTPUT
}

DESTDIR = $$OUTDIR/lib/$$RELEASE_TARGET

###########################
###      QT CONFIG      ###
###########################

TEMPLATE = lib
TARGET = qphidget-mock-qml
QT += qml quick
CONFIG += qt plugin

TARGET = $$qtLibraryTarget($$TARGET)
uri = com.captemulation.qphidget.mock

# Input
INCLUDEPATH += \
    src

SOURCES += \
    qphidget-mock-qml_plugin.cpp \
    src/QPMock888DeviceItem.cpp

HEADERS += \
    qphidget-mock-qml_plugin.h \
    src/QPMock888DeviceItem.h

OTHER_FILES = qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}



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

###########################
###      LIBRARIES      ###
###########################


# qphidget-mock library

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/qphidget-mock/ -lqphidget-mock
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/qphidget-mock/ -lqphidget-mockd
else:unix: LIBS += -L$$PWD/../lib/qphidget-mock/ -lqphidget-mock

INCLUDEPATH += $$PWD/../include/qphidget-mock
DEPENDPATH += $$PWD/../include/qphidget-mock
