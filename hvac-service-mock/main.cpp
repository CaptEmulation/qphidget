#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include "HttpDaemon.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/hvac-service-mock/main.qml"));
    viewer.showExpanded();

    HttpDaemon *daemon = new HttpDaemon(8080);
    daemon->resume();

    return app.exec();
}
