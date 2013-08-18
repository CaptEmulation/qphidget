#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

#include "QPInterfaceKitFactory.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QPManager *service = new QPManager();
    QPInterfaceKitFactory *deviceFactory = new QPInterfaceKitFactory(service);
    service->addDeviceInterface(QPInterfaceKitFactory::deviceClass(), deviceFactory);
    service->open();

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/qphidget/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
