
#Copyright 2013 John Dean, III
#
#Licensed under the Apache License, Version 2.0 (the "License");
#you may not use this file except in compliance with the License.
#You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
#Unless required by applicable law or agreed to in writing, software
#distributed under the License is distributed on an "AS IS" BASIS,
#WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#See the License for the specific language governing permissions and
#limitations under the License.


# Phidget library
unix: LIBS += -lphidget21

win32 {
    LIBS += "C:/Program Files/Phidgets/phidget21.lib"
    INCLUDEPATH += "C:/Program Files/Phidgets"
    HEADERS += "C:/Program Files/Phidgets/phidget21.h"
}


#QPhidget library

INCLUDEPATH += ../qphidget-lib/src
HEADERS += $$PWD/../qphidget-lib/src/*.h \
    src/QP888DeviceItem.h

# Qt Config

CONFIG(debug) {
    CONFIG += staticlib
}

TEMPLATE = lib
TARGET = qphidget-qml
QT += qml quick
CONFIG += qt plugin

TARGET = $$qtLibraryTarget($$TARGET)
uri = com.soapbubble.qphidget

# Input
INCLUDEPATH += src

SOURCES += \
    qphidget-qml_plugin.cpp \
    src/QPhidget.cpp \
    src/QP888DeviceItem.cpp

HEADERS += \
    qphidget-qml_plugin.h \
    src/QPhidget.h

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


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../qphidget-lib/ -lqphidget-lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../qphidget-lib/ -lqphidget-libd
else:unix: LIBS += -L$$PWD/../qphidget-lib/ -lqphidget-lib

INCLUDEPATH += $$PWD/../qphidget-lib
DEPENDPATH += $$PWD/../qphidget-lib

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../qphidget-lib/qphidget-lib.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../qphidget-lib/qphidget-libd.lib
else:unix: PRE_TARGETDEPS += $$PWD/../qphidget-lib/libqphidget-lib.a
