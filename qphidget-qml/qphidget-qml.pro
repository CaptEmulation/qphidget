
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



###########################
###    SETUP OUTPUT     ###
###########################

DEBUG_TARGET = qphidget-qmld
RELEASE_TARGET = qphidget-qml
OUTDIR = ..

CONFIG(debug, debug|release){
    TARGET = $$DEBUG_TARGET
}

CONFIG(release, debug|release){
    TARGET = $$RELEASE_TARGET
    DEFINES += QT_NO_DEBUG_OUTPUT
}

DESTDIR = $$OUTDIR/lib/$$RELEASE_TARGET

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

# qphidget-lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/qphidget/ -lqphidget-lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/qphidget/ -lqphidget-libd
else:unix: LIBS += -L$$PWD/../lib/qphidget/ -lqphidget-lib

INCLUDEPATH += $$PWD/../include/qphidget
DEPENDPATH += $$PWD/../include/qphidget

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/qphidget/qphidget-lib.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/qphidget/qphidget-libd.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/qphidget/libqphidget-lib.a


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
