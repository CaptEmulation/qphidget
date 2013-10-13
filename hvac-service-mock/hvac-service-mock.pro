# Add more folders to ship with the application, here
folder_01.source = qml/hvac-service-mock
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

# hvac-service-lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../hvac-service-lib/ -lhvac-service-lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../hvac-service-lib/ -lhvac-service-libd
else:unix: LIBS += -L$$PWD/../hvac-service-lib/ -lhvac-service-lib

INCLUDEPATH += $$PWD/../hvac-service-lib
DEPENDPATH += $$PWD/../hvac-service-lib

