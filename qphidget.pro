
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

DESTDIR      = $${OUT_PWD}

CONFIG(debug) {
    CONFIGURATION = debug
} else {
    CONFIGURATION = release
}

QPHIDGET_LIB_BUILD_PATH = $$PWD/qphidget-lib/$${CONFIGURATION}
QPHIDGET_QML_BUILD_PATH = $$PWD/qphidget-qml/$${CONFIGURATION}




# Phidget library
#unix {
#    LIBS += phidget21
#}

win32 {
    LIBS += "C:/Program Files/Phidgets/phidget21.lib"
    INCLUDEPATH += "C:/Program Files/Phidgets"
    HEADERS += "C:/Program Files/Phidgets/phidget21.h"
}

#QPhidget library
INCLUDEPATH += {$$PWD}/qphidget-lib/src {$$PWD}/qphidget-qml
HEADERS += {$$PWD}/qphidget-lib/src/*.h {$$PWD}/qphidget-lib/*.h

# Add more folders to ship with the application, here
folderQml.source = qml/qphidget
folderQml.target = qml
DEPLOYMENTFOLDERS = folderQml

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH += qphidget-qml/$${CONFIGURATION}

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()



SOURCES += \
    main.cpp

INCLUDEPATH += src

win32 {
    INCLUDEPATH += \
        "C:/Program Files/Phidgets"
}

# HEADERS +=

# Deployment

OTHER_FILES += \
        $${QPHIDGET_LIB} \
        $${QPHIDGET_QML} \
        $${QPHIDGET_QML_BUILD_PATH}/../qmldir

win32 {
    #...

    OTHER_FILES_WIN = $${OTHER_FILES}
    OTHER_FILES_WIN ~= s,/,\\,g
    DESTDIR_WIN = $${DESTDIR}
    DESTDIR_WIN ~= s,/,\\,g
    for(FILE,OTHER_FILES_WIN){
        QMAKE_POST_LINK +=$$quote(cmd /c copy /y $${FILE} $${DESTDIR_WIN}$$escape_expand(\n\t))
    }
}

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/qphidget-qml/ -lqphidget-qml
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/qphidget-qml/ -lqphidget-qmld
else:unix: LIBS += -L$$PWD/qphidget-qml/ -lqphidget-qml

INCLUDEPATH += $$PWD/qphidget-qml
DEPENDPATH += $$PWD/qphidget-qml

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/qphidget-qml/qphidget-qml.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/qphidget-qml/qphidget-qmld.lib
else:unix: PRE_TARGETDEPS += $$PWD/qphidget-qml/libqphidget-qml.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/qphidget-lib/ -lqphidget-lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/qphidget-lib/ -lqphidget-libd
else:unix: LIBS += -L$$PWD/qphidget-lib/ -lqphidget-lib

INCLUDEPATH += $$PWD/qphidget-lib
DEPENDPATH += $$PWD/qphidget-lib

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/qphidget-lib/qphidget-lib.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/qphidget-lib/qphidget-libd.lib
else:unix: PRE_TARGETDEPS += $$PWD/qphidget-lib/libqphidget-lib.a


unix: LIBS += -lphidget21
