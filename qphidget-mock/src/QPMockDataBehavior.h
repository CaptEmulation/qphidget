#ifndef QPMOCKDATABEHAVIOR_H
#define QPMOCKDATABEHAVIOR_H

#include "QPMockUpdateDelegate.h"
#include "QPMockDevice.h"
#include <QDataStream>
#include <QVariantMap>

class QPMockDataBehaviorPrivate;

class QPMockDataBehavior : public QPMockUpdateDelegate
{
    Q_OBJECT
    Q_PROPERTY(QVariantMap data READ data WRITE setData NOTIFY dataChanged)
    Q_PROPERTY(QPMockDevice *device READ device WRITE setDevice NOTIFY deviceChanged)
public:
    explicit QPMockDataBehavior(QObject *parent = 0);
    ~QPMockDataBehavior();

    QVariantMap data();
    QPMockDevice *device();
signals:
    void dataChanged(QVariantMap data);
    void deviceChanged(QPMockDevice *device);

public slots:
    void setData(QVariantMap data);
    void setDevice(QPMockDevice *device);

protected:
    void doUpdate(QPMockUpdateContext *context);

private:
    QScopedPointer<QPMockDataBehaviorPrivate> p;
};

#endif // QPMOCKDATABEHAVIOR_H
