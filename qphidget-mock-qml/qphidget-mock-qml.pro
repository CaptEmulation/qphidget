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

# qphidget-mock library

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../qphidget-mock/ -lqphidget-mock
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../qphidget-mock/ -lqphidget-mockd
else:unix: LIBS += -L$$PWD/../qphidget-mock/ -lqphidget-mock

INCLUDEPATH += $$PWD/../qphidget-mock/src\
    $$PWD/../qphidget-lib/src
DEPENDPATH += $$PWD/../qphidget-mock
