
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
macx:unix {
    LIBS += phidget21
}

win32 {
    LIBS += "C:/Program Files/Phidgets/phidget21.lib"
    INCLUDEPATH += "C:/Program Files/Phidgets"
    HEADERS += "C:/Program Files/Phidgets/phidget21.h"
}


#QPhidget library
unix {
    CONFIG(debug) {
        LIBS += "$$PWD/qphidget-lib/debug/qphidget-lib.so"
    } else {
        LIBS += "$$PWD/qphidget-lib/release/qphidget-lib.so"
    }
}
win32 {
    CONFIG(debug) {
        LIBS += "$$PWD/qphidget-lib/debug/qphidget-lib.lib"
    } else {
        LIBS += "$$PWD/qphidget-lib/release/qphidget-lib.lib"
    }
}

INCLUDEPATH += qphidget-lib/src
HEADERS += $$PWD/qphidget-lib/src/*.h

# Add more folders to ship with the application, here
folder_01.source = qml/qphidget
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

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

