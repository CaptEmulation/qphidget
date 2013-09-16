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

class QPMockDevicePrivate;

/**
  A mock of a connected phidget device

 * @brief The QPMockDevice class
 */
class QPMockDevice  : public QObject
{
    Q_OBJECT
    // Arbitray data for the sub-classes to set themselves to.  Sub-classes should implement doSetData
    Q_PROPERTY(QVariantMap data READ data WRITE setData NOTIFY dataChanged)

public:
    struct ConnectEvent {
        DeviceCallback fptr;
        void *userPtr;
    };

    explicit QPMockDevice(QObject *parent = 0);
    ~QPMockDevice();

    void attach();
    void detach();

    CPhidget_DeviceClass deviceClass();
    void setDeviceClass(CPhidget_DeviceClass deviceClass);

    void setAttachListener(int (*fptr)(CPhidgetHandle, void *), void *userPtr);
    void setDetachListener(int (*fptr)(CPhidgetHandle, void *), void *userPtrk);

    QVariantMap data();


signals:
    void dataChanged(QVariantMap data);

public slots:
    void setData(QVariantMap data);

protected slots:
    virtual void doSetData(const QVariantMap &data) = 0;

private:
    QScopedPointer<QPMockDevicePrivate> p;
};

Q_DECLARE_METATYPE(CPhidgetHandle)

#endif // QPMOCKDEVICE_H
