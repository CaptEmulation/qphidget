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

#include <QBitArray>
#include <QVariant>

struct IOCallback {
    CPhidgetInterfaceKitHandle phid;
    int (*fptr)(CPhidgetInterfaceKitHandle, void *, int, int);
    void *userPtr;
};

class QPMock888DevicePrivate
{
public:
    QPMock888Device *self;
    QList<IOCallback> mInputHandlers;
    QList<IOCallback> mOutputHandlers;

    QBitArray mInput;
    QBitArray mOutput;

    void initialize() {
        mInput = QBitArray(8);
        mOutput = QBitArray(8);;
        self->setDeviceClass(PHIDCLASS_INTERFACEKIT);
    }

    void setOnInputChange(CPhidgetInterfaceKitHandle phid, int (*fptr)(CPhidgetInterfaceKitHandle, void *, int, int), void *userPtr)
    {
        IOCallback callback;
        callback.phid = phid;
        callback.fptr = fptr;
        callback.userPtr = userPtr;
        mInputHandlers.append(callback);
    }

    void setOnOutputChange(CPhidgetInterfaceKitHandle phid, int (*fptr)(CPhidgetInterfaceKitHandle, void *, int, int), void *userPtr)
    {
        IOCallback callback;
        callback.fptr = fptr;
        callback.phid = phid;
        callback.userPtr = userPtr;
        mOutputHandlers.append(callback);
    }

    bool input(int index) {
        return mInput.at(index);
    }

    int setInput(int index, bool input) {
        mInput.setBit(index, input);

        foreach(IOCallback c, mInputHandlers) {
            c.fptr(c.phid, c.userPtr, index, input);
        }

        emit self->inputChanged(index, input);

        return 0;
    }

    bool output(int index) {
        return mOutput.at(index);
    }


    int setOutput(int index, bool output) {
        mOutput.setBit(index, output);

        foreach(IOCallback c, mOutputHandlers) {
            c.fptr(c.phid, c.userPtr, index, output);
        }

        emit self->outputChanged(index, output);

        return 0;
    }

    void doSetData(const QVariantMap &data) {
        QVariant vInput = data["digital"];
        if (vInput.canConvert(QVariant::Map)) {
            QVariantMap inputMap = vInput.toMap();
             for(int i = 0; i < NUM_OF_PORTS; i++) {
                 QString key = QString("%1").arg(i);
                 if (inputMap.contains(key)) {
                     setInput(i, inputMap.value(key).toBool());
                 }
             }
        } else if(vInput.canConvert(QVariant::String)) {
            QString inputs = vInput.toString();
            for(int i = 0; i < NUM_OF_PORTS; i++) {
                if (inputs.length() > i) {
                    QChar input = inputs.at(i);
                    if(input == '1') {
                        setInput(i, true);
                    } else if(input == '0') {
                        setInput(i, false);
                    }
                }
            }
        }
    }
};

QPMock888Device::QPMock888Device(qint32 id, QObject *parent)   :
    QPMockDevice(parent),
    p(new QPMock888DevicePrivate)
{
    p->self = this;
    setId(id);;
    p->initialize();
}

QPMock888Device::~QPMock888Device()
{
}

int QPMock888Device::setOnInputChange(CPhidgetInterfaceKitHandle phid, int (*fptr)(CPhidgetInterfaceKitHandle, void *, int, int), void *userPtr)
{
    p->setOnInputChange(phid, fptr, userPtr);
    return 0;

}

int QPMock888Device::setOnOutputChange(CPhidgetInterfaceKitHandle phid, int (*fptr)(CPhidgetInterfaceKitHandle, void *, int, int), void *userPtr)
{
    p->setOnOutputChange(phid, fptr, userPtr);
    return 0;
}

bool QPMock888Device::input(int index)
{
    return p->input(index);
}

int QPMock888Device::setInput(int index, bool input)
{
    return p->setInput(index, input);
}

bool QPMock888Device::output(int index)
{
    return p->output(index);
}

int QPMock888Device::setOutput(int index, bool output)
{
    return p->setOutput(index, output);
}

void QPMock888Device::doSetData(const QVariantMap &data)
{
    p->doSetData(data);
}
