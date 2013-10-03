#include "qphidget-mock-qml_plugin.h"
#include "QPMock888DeviceItem.h"
#include "QPMockFactory.h"
#include "QPMock.h"
#include <qqml.h>

void Qphidget_Mock_QmlPlugin::registerTypes(const char *uri)
{
    QPMock::getSingleton()->appendMock(new QPMock888Device(-1));
    // @uri com.captemulation.qphidget.mock
    qmlRegisterType<QPMock888DeviceItem>(uri, 1, 0, "Mock888Device");
}


