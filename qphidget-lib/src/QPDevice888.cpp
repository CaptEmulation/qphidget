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

#include "QPDevice888.h"

int inputHandler(CPhidgetInterfaceKitHandle phid, void *userPtr, int index, int inputState);

class QPDevice888Private
{
public:
    QPDevice888 *self;
    bool mConnected;
    bool mOpen;
    CPhidgetHandle mPhidget;
    CPhidgetInterfaceKitHandle mIfkPhidget;
    QList<QPDigitalIO *> mInputs;
    QList<QPDigitalIO *> mOutputs;

    void initialize() {
        // Initialize individual IO objects
        for(int i = 0; i < 8; i++) {
            mInputs.append(new QPDigitalIO(QPDigitalIO::Input, i, self));
            mOutputs.append(new QPDigitalIO(QPDigitalIO::Output, i, self));
        }

    }

    void open() {
        if (mConnected) {
            int err = CPhidgetInterfaceKit_create(&mIfkPhidget);
            err = CPhidgetInterfaceKit_set_OnInputChange_Handler(mIfkPhidget, inputHandler, this);
            err = CPhidget_open((CPhidgetHandle)mIfkPhidget, -1);
            mOpen = !err;
        }
    }

    void close() {
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
            emit self->connectedChanged();
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

QPDevice888::QPDevice888(QObject *parent) :
    QObject(parent),
    p(new QPDevice888Private)
{
    p->self = this;
    p->initialize();
}

QPDevice888::~QPDevice888()
{
    CPhidget_delete((CPhidgetHandle)p->mIfkPhidget);
}

void QPDevice888::open()
{
    p->open();
}

void QPDevice888::close()
{
    p->close();
}

bool QPDevice888::getInput(qint32 index)
{
    return p->getInput(index);
}

void QPDevice888::setOutput(qint32 index, bool value)
{
    p->setOutput(index, value);
}

bool QPDevice888::connected()
{
    return p->mConnected;
}


QList<QPDigitalIO *> QPDevice888::inputs()
{
    return p->mInputs;
}

QList<QPDigitalIO *> QPDevice888::outputs()
{
    return p->mOutputs;
}

CPhidgetHandle QPDevice888::phidget()
{
    return p->mPhidget;
}


void QPDevice888::setConnected(bool connected)
{
    p->setConnected(connected);
}

void QPDevice888::setPhidget(CPhidgetHandle phidget)
{
    p->setPhidget(phidget);
}

int inputHandler(CPhidgetInterfaceKitHandle phid, void *userPtr, int index, int inputState) {
    QPDevice888Private *instance = (QPDevice888Private *)userPtr;
    instance->setInput(index, inputState);
    return 0;
}

