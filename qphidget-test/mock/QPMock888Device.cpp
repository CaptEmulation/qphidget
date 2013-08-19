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

#include "QPMock888Device.h"

#include "QPMock.h"

struct InputCallback {
    int (*fptr)(CPhidgetInterfaceKitHandle, void *, int, int);
    void *userPtr;
};

class QPMock888DevicePrivate
{
public:
    QPMock888Device *self;
    QList<InputCallback> mInputHandlers;

    quint8 mInput;
    quint8 mOutput;

    void setOnInputChange(int (*fptr)(CPhidgetInterfaceKitHandle, void *, int, int), void *userPtr)
    {
        InputCallback callback;
        callback.fptr = fptr;
        callback.userPtr = userPtr;
        mInputHandlers.append(callback);
    }

    void initialize() {
        mInput = 0;
        mOutput = 0;
        self->setDeviceClass(PHIDCLASS_INTERFACEKIT);
        QPMock::singleton->appendMock(self);
    }

    int setInput(int index, bool input) {
        if (input) {
            mInput |= input << index;
        } else {
            mInput &= input << index;
        }

        foreach(InputCallback c, mInputHandlers) {
            c.fptr(self, c.userPtr, index, input);
        }
        return 0;
    }

    int setOutput(int index, bool output) {
        if (output) {
            mOutput |= output << index;
        } else {
            mOutput &= output << index;
        }

        // TODO: create and notify listeners
        return 0;
    }
};

QPMock888Device::QPMock888Device(QObject *parent) :
    QPMockDevice(parent),
    p(new QPMock888DevicePrivate)
{
    p->self = this;
    p->initialize();
}

QPMock888Device::~QPMock888Device()
{
}

int QPMock888Device::setOnInputChange(int (*fptr)(CPhidgetInterfaceKitHandle, void *, int, int), void *userPtr)
{
    p->setOnInputChange(fptr, userPtr);
    return 0;

}

int QPMock888Device::setInput(int index, bool input)
{
    return p->setInput(index, input);
}

int QPMock888Device::setOutput(int index, bool output)
{
    return p->setOutput(index, output);
}
