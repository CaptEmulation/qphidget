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

#include "QPInterfaceKitFactory.h"

#include <QMap>
#include <QMetaObject>

class QPInterfaceKitFactoryPrivate
{
public:
    QPInterfaceKitFactory *self;
    QList<QP888Device *> mDevices;
    QP888Device *mLast;

    void createDeviceForHandle(CPhidgetHandle phidget) {
        bool containsDevice = false;
        foreach(QP888Device *d, mDevices) {
            if (d->phidget() == phidget) {
                containsDevice = true;
                d->setConnected(true);
                break;
            }
        }

        if (!containsDevice) {
            QP888Device *device = new QP888Device();
            device->moveToThread(self->thread());
            mDevices.append(device);
            device->setPhidget(phidget);
            device->setConnected(true);
            mLast = device;
            emit self->deviceAvailable(device);
            device->open();
        }
    }

    void deviceAttached(CPhidgetHandle phidget) {
        QMetaObject::invokeMethod(self,  "createDeviceForHandle", Qt::DirectConnection, Q_ARG(CPhidgetHandle, phidget));
    }

    void deviceDetached(CPhidgetHandle phidget) {
        foreach(QP888Device *d, mDevices) {
            if (d->phidget() == phidget) {
                d->setConnected(false);
                break;
            }
        }
    }
};

QPInterfaceKitFactory::QPInterfaceKitFactory(QObject *parent) :
    QObject(parent),
    p(new QPInterfaceKitFactoryPrivate)
{
    p->self = this;
    p->mLast = 0;
}

QPInterfaceKitFactory::~QPInterfaceKitFactory()
{
}

void QPInterfaceKitFactory::deviceAttached(CPhidgetHandle phidget)
{
    p->deviceAttached(phidget);
}

void QPInterfaceKitFactory::deviceDetached(CPhidgetHandle phidget)
{
    p->deviceDetached(phidget);
}

void QPInterfaceKitFactory::createDeviceForHandle(CPhidgetHandle handle)
{
    p->createDeviceForHandle(handle);
}

QP888Device *QPInterfaceKitFactory::getDevice()
{
    return p->mLast;
}

