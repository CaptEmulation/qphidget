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

#include "QPMockDevice.h"
#include "QPMock.h"

class QPMockDevicePrivate
{
public:
    QPMockDevice *self;
    QVariantMap mData;
    CPhidget_DeviceClass mDeviceClass;
    QList<QPMockDevice::ConnectEvent> mAttachListeners;
    QList<QPMockDevice::ConnectEvent> mDetachListeners;

    QVariantMap data() {
        return mData;
    }

    void setData(QVariantMap data) {
        if (mData != data) {
            mData = data;
            emit self->dataChanged(data);
        }
    }

    void setAttachListener(QPMockDevice::ConnectEvent callback) {
        mAttachListeners.append(callback);
    }

    void setDetachListener(QPMockDevice::ConnectEvent callback) {
        mDetachListeners.append(callback);
    }

    void attach() {
        QPMock::singleton->attached(self);
        foreach(QPMockDevice::ConnectEvent e, mAttachListeners) {
            e.fptr(self, e.userPtr);
        }
    }

    void detach() {
        // TODO detach from manager
        foreach(QPMockDevice::ConnectEvent e, mDetachListeners) {
            e.fptr(self, e.userPtr);
        }
    }
};

QPMockDevice::QPMockDevice(QObject *parent) :
    QObject(parent),
    p(new QPMockDevicePrivate)
{
    p->self = this;
    QObject::connect(this, SIGNAL(dataChanged(QVariantMap)), this, SLOT(doSetData(QVariantMap)));
}

QPMockDevice::~QPMockDevice()
{
}

void QPMockDevice::attach()
{
    p->attach();
}

void QPMockDevice::detach()
{
    p->detach();
}

CPhidget_DeviceClass QPMockDevice::deviceClass()
{
    return p->mDeviceClass;
}

void QPMockDevice::setDeviceClass(CPhidget_DeviceClass deviceClass)
{
    p->mDeviceClass = deviceClass;
}

void QPMockDevice::setAttachListener(int (*fptr)(CPhidgetHandle, void *), void *userPtr)
{
    QPMockDevice::ConnectEvent callback;
    callback.fptr = fptr;
    callback.userPtr = userPtr;
    p->setAttachListener(callback);
}

void QPMockDevice::setDetachListener(int (*fptr)(CPhidgetHandle, void *), void *userPtr)
{
    QPMockDevice::ConnectEvent callback;
    callback.fptr = fptr;
    callback.userPtr = userPtr;
    p->setDetachListener(callback);
}

QVariantMap QPMockDevice::data()
{
    return p->data();
}

void QPMockDevice::setData(QVariantMap data)
{
    p->setData(data);
}

