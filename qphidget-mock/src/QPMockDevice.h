/**
Copyright 2013 John Dean, III

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/


#ifndef QPMOCKDEVICE_H
#define QPMOCKDEVICE_H

#include <QObject>
#include <QVariantMap>
#include "phidget21.h"
#include "IMockDevice.h"
#include "UnattachedMockDevice.h"

class QPMockDevicePrivate;

/**
  A mock of a connected phidget device

 * @brief The QPMockDevice class
 */
class QPMockDevice  : public QObject, public IMockDevice
{
    Q_OBJECT
    Q_INTERFACES(IMockDevice)
    // Arbitray data for the sub-classes to set themselves to.  Sub-classes should implement doSetData
    Q_PROPERTY(QVariantMap data READ data WRITE setData NOTIFY dataChanged)
    Q_PROPERTY(qint32 id READ id WRITE setId NOTIFY idChanged)
public:

    explicit QPMockDevice(QObject *parent = 0);
    ~QPMockDevice();

    void attach();
    bool isAttached();
    void detach();

    qint32 id() const;

    CPhidget_DeviceClass deviceClass() const;
    void setDeviceClass(CPhidget_DeviceClass deviceClass);

    void setAttachListener(int (*fptr)(CPhidgetHandle, void *), void *userPtr);
    void setDetachListener(int (*fptr)(CPhidgetHandle, void *), void *userPtrk);

    void notifyAttached();
    void notifyDetached();

    QList<IMockDevice::ConnectEvent> attachHandlers();
    void setAttachHandlers(QList<IMockDevice::ConnectEvent> attachHandlers);
    QList<IMockDevice::ConnectEvent> detachHandlers();
    void setDetachHandlers(QList<IMockDevice::ConnectEvent> detachHandlers);

    QVariantMap data();

signals:
    void dataChanged(QVariantMap data);
    void idChanged(qint32 id);

public slots:
    void setData(QVariantMap data);
    void setId(qint32 id);

protected slots:
    virtual void doSetData(const QVariantMap &data) = 0;

private:
    QScopedPointer<QPMockDevicePrivate> p;
};


#endif // QPMOCKDEVICE_H
