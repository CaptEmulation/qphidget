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

#include <QMap>
#include "QPMock888Device.h"

QPMock* QPMock::singleton = Q_NULLPTR;

struct ConnectCallback {
    int (*callback)(CPhidgetHandle, void *);
    void *context;
};

struct ErrorCallback {
    int (*callback)(CPhidgetManagerHandle, void *, int, const char *);
    void *context;
};

class QPMockPrivate
{
public:
    bool mConnected;
    QMap<CPhidgetManagerHandle, ConnectCallback> attachHandlers;
    QMap<CPhidgetManagerHandle, ConnectCallback> detachHandlers;
    QMap<CPhidgetManagerHandle, ErrorCallback> errorHandlers;
    QList<CPhidgetHandle> mocks;
};

QPMock::QPMock(QObject *parent) :
    QObject(parent),
    p(new QPMockPrivate)
{
    p->mConnected = false;
    singleton = this;
}

QPMock::~QPMock()
{
}

void QPMock::reset()
{
    while(!p->mocks.empty()) {
        p->mocks.removeLast();
    }
    p->attachHandlers = QMap<CPhidgetManagerHandle, ConnectCallback>();
    p->detachHandlers = QMap<CPhidgetManagerHandle, ConnectCallback>();
    p->errorHandlers = QMap<CPhidgetManagerHandle, ErrorCallback>();
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

void QPMock::attached(CPhidgetHandle device)
{
    foreach(ConnectCallback cc, p->attachHandlers) {
        cc.callback(device, cc.context);
    }
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

QList<CPhidgetHandle> QPMock::mocks()
{
    return p->mocks;
}

void QPMock::appendMock(CPhidgetHandle device)
{
    p->mocks.append(device);
}

CPhidgetHandle QPMock::getMockOfClass(CPhidget_DeviceClass deviceClass)
{
    foreach(QPMockDevice *h, p->mocks) {
        if (h->deviceClass() == deviceClass) {
            return h;
        }
    }
    return 0;
}

