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

#include "QP888Device.h"

int inputHandler(CPhidgetInterfaceKitHandle phid, void *userPtr, int index, int inputState);
int attachHandler(CPhidgetHandle phid, void *userPtr);
int detachHandler(CPhidgetHandle phid, void *userPtr);

class QP888DevicePrivate
{
public:
    QP888Device *self;
    bool mConnected;
    bool mOpen;
    CPhidgetHandle mPhidget;
    CPhidgetInterfaceKitHandle mIfkPhidget;
    QList<QPDigitalIO *> mInputs;
    QList<QPDigitalIO *> mOutputs;

    void initialize() {
        mPhidget = Q_NULLPTR;

        // Initialize individual IO objects
        for(int i = 0; i < 8; i++) {
            mInputs.append(new QPDigitalIO(QPDigitalIO::Input, i, self));
            mOutputs.append(new QPDigitalIO(QPDigitalIO::Output, i, self));
        }

    }

    void open() {
        int err = CPhidgetInterfaceKit_create(&mIfkPhidget);

        if (mPhidget == Q_NULLPTR) {
            setPhidget((CPhidgetHandle)mIfkPhidget);
        }

        err = CPhidget_set_OnAttach_Handler((CPhidgetHandle)mIfkPhidget, attachHandler, this);
        err = CPhidget_set_OnDetach_Handler((CPhidgetHandle)mIfkPhidget, detachHandler, this);
        err = CPhidgetInterfaceKit_set_OnInputChange_Handler(mIfkPhidget, inputHandler, this);
        err = CPhidget_open((CPhidgetHandle)mIfkPhidget, -1);
        mOpen = !err;
    }

    void close() {
        setConnected(false);
        CPhidget_close((CPhidgetHandle)mIfkPhidget);
    }

    void setPhidget(CPhidgetHandle phidget) {
        if (mPhidget != phidget) {
            mPhidget = phidget;
        }
    }

    void setConnected(bool connected) {
        if (connected != mConnected) {
            mConnected = connected;
            if (connected) {
                // Inform output digits about IFk handler so that they can post there changes
                foreach(QPDigitalIO *output, mOutputs) {
                    output->setIfk(mIfkPhidget);
                }
            } else {
                // Turn off phidget posting of outputs
                foreach(QPDigitalIO *output, mOutputs) {
                    output->setIfk(Q_NULLPTR);
                }
            }
            emit self->connectedChanged(connected);
        }
    }

    bool getInput(qint32 index) {
        return mInputs.at(index)->state();
    }

    void setInput(qint32 index, bool value) {
        mInputs.at(index)->setState(value);
    }

    void setOutput(qint32 index, bool value) {
        mOutputs.at(index)->setState(value);
    }
};

QP888Device::QP888Device(QObject *parent) :
    QObject(parent),
    p(new QP888DevicePrivate)
{
    p->self = this;
    p->initialize();
}

QP888Device::~QP888Device()
{
    CPhidget_close((CPhidgetHandle)p->mIfkPhidget);
    CPhidget_delete((CPhidgetHandle)p->mIfkPhidget);
}

void QP888Device::open()
{
    p->open();
}

void QP888Device::close()
{
    p->close();
}

bool QP888Device::getInput(qint32 index)
{
    return p->getInput(index);
}

void QP888Device::setOutput(qint32 index, bool value)
{
    p->setOutput(index, value);
}

bool QP888Device::connected()
{
    return p->mConnected;
}


QList<QPDigitalIO *> QP888Device::inputs()
{
    return p->mInputs;
}

QList<QPDigitalIO *> QP888Device::outputs()
{
    return p->mOutputs;
}

CPhidgetHandle QP888Device::phidget()
{
    return p->mPhidget;
}


void QP888Device::setConnected(bool connected)
{
    p->setConnected(connected);
}

void QP888Device::setPhidget(CPhidgetHandle phidget)
{
    p->setPhidget(phidget);
}

int inputHandler(CPhidgetInterfaceKitHandle phid, void *userPtr, int index, int inputState) {
    QP888DevicePrivate *instance = (QP888DevicePrivate *)userPtr;
    instance->setInput(index, inputState);
    return 0;
}

int attachHandler(CPhidgetHandle phid, void *userPtr) {
    QP888DevicePrivate *instance = (QP888DevicePrivate *)userPtr;
    instance->setConnected(true);
    return 0;
}

int detachHandler(CPhidgetHandle phid, void *userPtr) {
    QP888DevicePrivate *instance = (QP888DevicePrivate *)userPtr;
    instance->setConnected(false);
    return 0;
}
