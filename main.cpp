#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

#include "qphidget-qml/qphidget-qml_plugin.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Qphidget_QmlPlugin plugin;
    plugin.registerTypes("com.soapbubble.qphidget");

    QtQuick2ApplicationViewer viewer;
    viewer.addImportPath(".");
    viewer.setMainQmlFile(QStringLiteral("qml/qphidget/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
