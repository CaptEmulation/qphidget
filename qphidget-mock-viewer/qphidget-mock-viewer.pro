# Add more folders to ship with the application, here
folder_01.source = qml/qphidget-mock-viewer
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

# qphidget-mock-qml

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../qphidget-mock-qml/ -lqphidget-mock-qml
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../qphidget-mock-qml/ -lqphidget-mock-qmld
else:unix: LIBS += -L$$PWD/../qphidget-mock-qml -lqphidget-mock-qml

INCLUDEPATH += $$PWD/../qphidget-mock-qml
DEPENDPATH += $$PWD/../qphidget-mock-qml

# qphidget-mock

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../qphidget-mock/ -lqphidget-mock
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../qphidget-mock/ -lqphidget-mockd
else:unix: LIBS += -L$$PWD/../qphidget-mock -lqphidget-mock

INCLUDEPATH += $$PWD/../qphidget-mock/src\
    $$PWD/../qphidget-lib/src
DEPENDPATH += $$PWD/../qphidget-mock

# qphidget-qml

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../qphidget-qml/ -lqphidget-qml
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../qphidget-qml/ -lqphidget-qmld
else:unix: LIBS += -L$$PWD/../qphidget-qml/ -lqphidget-qml

INCLUDEPATH += $$PWD/../qphidget-qml
DEPENDPATH += $$PWD/../qphidget-qml

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../qphidget-qml/qphidget-qml.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../qphidget-qml/qphidget-qmld.lib
else:unix: PRE_TARGETDEPS += $$PWD/../qphidget-qml/libqphidget-qml.a


#QPhidget library will be rebuilt from sources linked against the test mock library

INCLUDEPATH += $$PWD/../qphidget-lib/src
HEADERS += $$PWD/../qphidget-lib/src/*.h
SOURCES += $$PWD/../qphidget-lib/src/*.cpp

OTHER_FILES += \
    ../qml/DigitalOutput.qml \
    ../qml/DigitalInput.qml \
    ../qml/DigitalOutput.qml \
    ../qml/IOBox.qml \
    ../qml/Ifk888Tester.qml \
    ../qml/MockIFK888.qml
