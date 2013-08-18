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

#include "QPManager.h"
#include "phidget21.h"

#include <functional>
#include <QDebug>
#include <QMap>

int _AttachHandler(CPhidgetHandle phid, void *userPtr);
int _DetachHandler(CPhidgetHandle phid, void *userPtr);
int _ErrorHandler(CPhidgetManagerHandle MAN, void *usrptr, int Code, const char *Description);


class QPManagerPrivate
{
public:
    QPManager *self;
    CPhidgetManagerHandle mPhidgetManager;
    QMap<CPhidget_DeviceClass, QPManagerDelegate *> mDelegates;

    bool mReady;

    void initialize() {
        CPhidget_enableLogging(PHIDGET_LOG_VERBOSE, NULL);

        //create the Manager object
        CPhidgetManager_create(&mPhidgetManager);

        //Set the handlers to be run when the device is plugged in or opened from software, unplugged or closed from software, or generates an error.
        CPhidgetManager_set_OnAttach_Handler(mPhidgetManager, _AttachHandler, this);
        CPhidgetManager_set_OnDetach_Handler(mPhidgetManager, _DetachHandler, this);
        CPhidgetManager_set_OnError_Handler(mPhidgetManager, _ErrorHandler, this);

        CPhidgetManager_open(mPhidgetManager);

    }

    void addDeviceInterface(CPhidget_DeviceClass deviceClass, QPManagerDelegate *delegate) {
        mDelegates.insert(deviceClass, delegate);
    }

    void loadDevices() {
        int err = CPhidgetManager_create(&mPhidgetManager);
        err = CPhidgetManager_open(mPhidgetManager);

        // Get the list of devices
        CPhidgetHandle *devices;
        int count;

        err = CPhidgetManager_getAttachedDevices(mPhidgetManager, &devices, &count);

        for (int i = 0; i < count; i ++) {
            CPhidget_DeviceClass deviceClass;
            CPhidget_getDeviceClass(devices[i], &deviceClass);
            if (mDelegates.contains(deviceClass)) {
                QPManagerDelegate *delegate = mDelegates[deviceClass];
                delegate->deviceAttached(devices[i]);
            }
        }

        CPhidgetManager_freeAttachedDevicesArray(devices);
    }

    int attachHandler(CPhidgetHandle phid)
    {
        loadDevices();
        emit self->readyChanged();
        emit self->deviceAttached(phid);
        return 0;
    }

    int detachHandler(CPhidgetHandle phid)
    {
        return 0;
    }

    int errorHandler(int Code, const char *Description)
    {
        qDebug()<< QString("Error handled. %d - %s").arg(Code).arg(Description);
        return 0;
    }
};

QPManager::QPManager(QObject *parent) :
    QObject(parent),
    p(new QPManagerPrivate)
{
    CPhidget_enableLogging(PHIDGET_LOG_VERBOSE, NULL);
    p->self = this;
    p->mPhidgetManager = 0;
    p->initialize();
}

QPManager::~QPManager()
{
    if (p->mPhidgetManager) {
        CPhidgetManager_delete(p->mPhidgetManager);
    }
}

void QPManager::open()
{
    p->initialize();
}

void QPManager::addDeviceInterface(CPhidget_DeviceClass deviceClass, QPManagerDelegate *delegate)
{
    p->addDeviceInterface(deviceClass, delegate);
}

bool QPManager::ready()
{
    return p->mReady;
}



int _AttachHandler(CPhidgetHandle phid, void *userPtr) {
    QPManagerPrivate *instance = (QPManagerPrivate *)userPtr;
    return std::mem_fun(&QPManagerPrivate::attachHandler)(instance, phid);
}

int _DetachHandler(CPhidgetHandle phid, void *userPtr) {
    QPManagerPrivate *instance = (QPManagerPrivate *)userPtr;
    return std::mem_fun(&QPManagerPrivate::detachHandler)(instance, phid);
}

int _ErrorHandler(CPhidgetManagerHandle MAN, void *userPtr, int Code, const char *Description) {
    QPManagerPrivate *instance = (QPManagerPrivate *)userPtr;
    //return std::mem_fun(&PhidgetServicePrivate::errorHandler)(instance, Code, Description);
    return 0;
}
