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

# Qt Config

QT       += testlib

QT       -= gui

TARGET = tst_Phidget
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

#QPhidget library will be rebuilt from sources linked against the test mock library

INCLUDEPATH += $$PWD/../qphidget-lib/src
HEADERS += $$PWD/../qphidget-lib/src/*.h
SOURCES += $$PWD/../qphidget-lib/src/*.cpp

# Test Sources

SOURCES += tst_Phidget.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += $$PWD/../wphidget-mock/src/phidget21.h

#qphidget-mock library

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../qphidget-mock/ -lqphidget-mock
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../qphidget-mock/ -lqphidget-mockd
else:unix: LIBS += -L$$PWD/../qphidget-mock/ -lqphidget-mock

INCLUDEPATH += $$PWD/../qphidget-mock/src
DEPENDPATH += $$PWD/../qphidget-mock
