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
    CPhidgetHandle mHandle;
    qint32 mId;
    bool mAttached;
    QVariantMap mData;
    CPhidget_DeviceClass mDeviceClass;
    QList<IMockDevice::ConnectEvent> mAttachListeners;
    QList<IMockDevice::ConnectEvent> mDetachListeners;
    QPMockDevice *self;

    QVariantMap data() {
        return mData;
    }

    void setData(QVariantMap data) {
        if (mData != data) {
            mData = data;
            emit self->dataChanged(data);
        }
    }

    qint32 id() {
        return mId;
    }

    void setId(qint32 id) {
        if (mId != id) {
            mId = id;
            emit self->idChanged(id);
        }
    }

    void setAttachListener(IMockDevice::ConnectEvent callback) {
        mAttachListeners.append(callback);
    }

    void setDetachListener(IMockDevice::ConnectEvent callback) {
        mDetachListeners.append(callback);
    }

    QList<IMockDevice::ConnectEvent> attachHandlers() {
        return mAttachListeners;
    }

    void setAttachHandlers(QList<IMockDevice::ConnectEvent> attachHandlers) {
        mAttachListeners = attachHandlers;
    }

    QList<IMockDevice::ConnectEvent> detachHandlers() {
        return mDetachListeners;
    }

    void setDetachHandlers(QList<IMockDevice::ConnectEvent> detachHandlers) {
        mDetachListeners = detachHandlers;
    }

    void attach() {
        mAttached = true;
        notifyAttached();
    }

    void notifyAttached() {
        mHandle = QPMock::getSingleton()->attached(self);
        foreach(QPMockDevice::ConnectEvent e, mAttachListeners) {
            e.fptr(mHandle, e.userPtr);
        }
    }

    void detach() {
        mAttached = false;
    }

    void notifyDetached() {
        foreach(QPMockDevice::ConnectEvent e, mDetachListeners) {
            e.fptr(mHandle, e.userPtr);
        }
    }
};

QPMockDevice::QPMockDevice(QObject *parent) :
    QObject(parent),
    IMockDevice(),
    p(new QPMockDevicePrivate)
{
    p->self = this;
    p->mAttached = false;
    p->mId = -1;
    QObject::connect(this, SIGNAL(dataChanged(QVariantMap)), this, SLOT(doSetData(QVariantMap)));
}

QPMockDevice::~QPMockDevice()
{
}

void QPMockDevice::attach()
{
    p->attach();
}

bool QPMockDevice::isAttached()
{
    return p->mAttached;
}

void QPMockDevice::detach()
{
    p->detach();
}

qint32 QPMockDevice::id() const
{
    return p->id();
}

CPhidget_DeviceClass QPMockDevice::deviceClass() const
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

void QPMockDevice::notifyAttached()
{
    p->notifyAttached();
}

void QPMockDevice::notifyDetached()
{
    p->notifyDetached();
}

QList<IMockDevice::ConnectEvent> QPMockDevice::attachHandlers()
{
    return p->attachHandlers();
}

void QPMockDevice::setAttachHandlers(QList<IMockDevice::ConnectEvent> attachHandlers)
{
    p->setAttachHandlers(attachHandlers);
}

QList<IMockDevice::ConnectEvent> QPMockDevice::detachHandlers()
{
    return p->detachHandlers();
}

void QPMockDevice::setDetachHandlers(QList<IMockDevice::ConnectEvent> detachHandlers)
{
    p->setDetachHandlers(detachHandlers);
}

QVariantMap QPMockDevice::data()
{
    return p->data();
}

void QPMockDevice::setData(QVariantMap data)
{
    p->setData(data);
}

void QPMockDevice::setId(qint32 id)
{
    p->setId(id);
}

