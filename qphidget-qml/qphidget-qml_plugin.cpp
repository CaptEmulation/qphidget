#include "qphidget-qml_plugin.h"
#include "QP888DeviceItem.h"

#include <qqml.h>

void Qphidget_QmlPlugin::registerTypes(const char *uri)
{
    // @uri com.soapbubble.qphidget
    qmlRegisterType<QP888DeviceItem>(uri, 1, 0, "IFK888");
}


