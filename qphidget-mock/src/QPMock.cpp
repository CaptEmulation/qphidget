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

#include "QPMock.h"
#include "QPMockHandle.h"

#include <QMap>
#include "QPMock888Device.h"

QPMock* singleton = Q_NULLPTR;

struct ConnectCallback {
    int (*callback)(CPhidgetHandle, void *);
    void *context;
};

struct ErrorCallback {
    int (*callback)(CPhidgetManagerHandle, void *, int, const char *);
    void *context;
};

typedef QMultiMap<CPhidget_DeviceClass, QSharedPointer<QPMockHandle> > QPDeviceMap;

class QPMockPrivate
{

public:
    bool mConnected;
    QPDeviceMap mMocks;
    QMap<CPhidgetManagerHandle, ConnectCallback> attachHandlers;
    QMap<CPhidgetManagerHandle, ConnectCallback> detachHandlers;
    QMap<CPhidgetManagerHandle, ErrorCallback> errorHandlers;
    QList<CPhidgetHandle> mocks;

    void reset() {
        foreach(CPhidget_DeviceClass key, mMocks.keys()) {
            QPDeviceMap::iterator itr = mMocks.find(key);
            while (itr != mMocks.end() && itr.key() == key) {
                (**itr.value()).clear();
                ++itr;
            }

            mMocks.remove(key);
        }

        attachHandlers = QMap<CPhidgetManagerHandle, ConnectCallback>();
        detachHandlers = QMap<CPhidgetManagerHandle, ConnectCallback>();
        errorHandlers = QMap<CPhidgetManagerHandle, ErrorCallback>();
    }

    CPhidgetHandle getMockOfClass(CPhidget_DeviceClass deviceClass, qint32 id = -1) {

        QPDeviceMap::const_iterator itr = mMocks.find(deviceClass);
        while (itr != mMocks.end() && itr.key() == deviceClass) {
            if((**itr.value())->id() == id) {
                return itr.value().data();
            }
            ++itr;
        }
        return 0;
    }

    void appendMock(IMockDevice *mock) {
        // Check if we already have a referece
        QPMockHandle *device = getMockOfClass(mock->deviceClass(), mock->id());

        if(!device) {
//            CPhidget_DeviceClass deviceClass = (**device)->deviceClass();
//            QPDeviceMap::iterator itr = mMocks.find(deviceClass);
//            while (itr != mMocks.end() && itr.key() == deviceClass) {
//                QSharedPointer<IMockDevice> iPtr = **itr.value();
//                if (!iPtr.isNull() && iPtr->id() == (**device)->id() || iPtr->id() == -1) {
//                    itr.value()->reset(mock);
//                }
//                ++itr;
//            }
//        } else {
            mMocks.insert(mock->deviceClass(), QSharedPointer<QPMockHandle>(new QPMockHandle(mock)));
        }
    }

    void removeMock(IMockDevice *mock) {
        // Check if we already have a referece
        QSharedPointer<QPMockHandle> device(getMockOfClass(mock->deviceClass(), mock->id()));

        if(!device.isNull()) {
            CPhidget_DeviceClass deviceClass = (**device)->deviceClass();
            QPDeviceMap::const_iterator itr = mMocks.find(deviceClass);
            while (itr != mMocks.end() && itr.key() == deviceClass) {
                if((**itr.value())->id() == (**device)->id()) {
                    mMocks.remove(itr.key(), itr.value());
                }
                ++itr;
            }
        }

    }
};

QPMock::QPMock(QObject *parent) :
    QObject(parent),
    p(new QPMockPrivate)
{
    p->mConnected = false;
}

QPMock::~QPMock()
{
}

void QPMock::reset()
{
    p->reset();
}

bool QPMock::isConnected()
{
    return p->mConnected;
}

void QPMock::setConnected(bool connected)
{
    p->mConnected = connected;
}


int QPMock::appendAttachListener(CPhidgetManagerHandle phidm, int (*fptr)(CPhidgetHandle, void *), void *userPtr)
{
    ConnectCallback data;
    data.callback = fptr;
    data.context = userPtr;
    p->attachHandlers.insert(phidm, data);
    return 0;
}

CPhidgetHandle QPMock::attached(IMockDevice *mock)
{
    CPhidgetHandle device = getMockOfClass(mock->deviceClass(), mock->id());
    foreach(ConnectCallback cc, p->attachHandlers) {
        cc.callback(device, cc.context);
    }
    return device;
}

int QPMock::appendDetachListener(CPhidgetManagerHandle phidm, int (*fptr)(CPhidgetHandle, void *), void *userPtr)
{
    ConnectCallback data;
    data.callback = fptr;
    data.context = userPtr;
    p->detachHandlers.insert(phidm, data);
    return 0;
}

int QPMock::appendErrorListener(CPhidgetManagerHandle phidm, int (*fptr)(CPhidgetManagerHandle, void *, int, const char *), void *userPtr)
{
    ErrorCallback data;
    data.callback = fptr;
    data.context = userPtr;
    p->errorHandlers.insert(phidm, data);
    return 0;
}

int QPMock::getAttachedDevices(CPhidgetManagerHandle phidm, CPhidgetHandle *phidArray[], int *count)
{
    CPhidgetHandle *array = new CPhidgetHandle[p->mocks.length()];
    *phidArray = array;
    QListIterator<CPhidgetHandle> itr(p->mocks);
    *count = 0;

    while (itr.hasNext()) {
        array[*count] = itr.next();
        *count = *count + 1;
    }

    return 0;
}

QPMock *QPMock::getSingleton()
{
    if (singleton == Q_NULLPTR) {
        singleton = new QPMock();
    }
    return singleton;
}

QList<CPhidgetHandle> QPMock::mocks()
{
    return p->mocks;
}

void QPMock::appendMock(IMockDevice *mock)
{
    p->appendMock(mock);
}

void QPMock::removeMock(IMockDevice *mock)
{
    p->removeMock(mock);
}

CPhidgetHandle QPMock::getMockOfClass(CPhidget_DeviceClass deviceClass, qint32 id)
{
    return p->getMockOfClass(deviceClass, id);
}

