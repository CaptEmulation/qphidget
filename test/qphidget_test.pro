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


QT       += testlib

QT       -= gui

TARGET = tst_Phidget
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_Phidget.cpp \
    phidget21.cpp \
    mock/QPMock.cpp \
    mock/QPMock888Device.cpp \
    mock/QPMockDevice.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += . ../src mock

SOURCES += \
    ../src/QPInterfaceKitFactory.cpp \
    ../src/QPDevice888.cpp \
    ../src/QPManager.cpp \
    ../src/QPDigitalIO.cpp


HEADERS += \
    phidget21.h \
    ../src/QPInterfaceKitFactory.h \
    ../src/QPDevice888.h \
    ../src/QPManager.h \
    ../src/QPDigitalIO.h \
    mock/QPMock.h \
    mock/QPMock888Device.h \
    mock/QPMockDevice.h



