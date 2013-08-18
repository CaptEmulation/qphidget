#ifndef QPHIDGET_QML_PLUGIN_H
#define QPHIDGET_QML_PLUGIN_H

#include <QQmlExtensionPlugin>

class Qphidget_QmlPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")
    
public:
    void registerTypes(const char *uri);
};

#endif // QPHIDGET_QML_PLUGIN_H

