#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include "qphidget-mock-qml_plugin.h"
#include "qphidget-qml_plugin.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Qphidget_Mock_QmlPlugin mockPlugin;
    mockPlugin.registerTypes("com.captemulation.qphidget.mock");

    Qphidget_QmlPlugin plugin;
    plugin.registerTypes("com.captemulation.qphidget");

    QtQuick2ApplicationViewer testViewer;
    testViewer.setMainQmlFile(QStringLiteral("qml/qphidget-mock-viewer/Ifk888Tester.qml"));
    testViewer.setTitle("Tester");
    testViewer.showExpanded();

    QtQuick2ApplicationViewer mockViewer;
    mockViewer.setMainQmlFile(QStringLiteral("qml/qphidget-mock-viewer/MockIFK888.qml"));
    mockViewer.setTitle("Mock IFK888");
    mockViewer.showExpanded();

    return app.exec();
}
