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


#include "phidget21.h"
#include "QPMock.h"
#include "QPMockDevice.h"
#include "QPMockHandle.h"
#include "QPMock888Device.h"

#include <QMap>
#include <QSharedPointer>


int CPhidget_open(CPhidgetHandle phid, int serialNumber)
{
    QSharedPointer<QPMockDevice> device = (**phid).dynamicCast<QPMockDevice>();
    if (!device.isNull()) {
       device->notifyAttached();
    }
    return 0;
}

int CPhidget_close(CPhidgetHandle phid)
{
    QSharedPointer<QPMockDevice> device = (**phid).dynamicCast<QPMockDevice>();
    if (!device.isNull()) {
       device->notifyDetached();
    }
    return 0;
}


int CPhidget_delete(CPhidgetHandle phid)
{
    // do nothing
    return 0;
}



// Sets connected to true for further asserts
int CPhidgetManager_create(CPhidgetManagerHandle *phidm)
{
    QPMock::getSingleton()->setConnected(true);
    return 0;
}

// Asserts we are connected
int CPhidgetManager_open(CPhidgetManagerHandle phidm)
{
    Q_ASSERT(QPMock::getSingleton()->isConnected());
    return 0;
}

// Asserts we are connected
int CPhidgetManager_close(CPhidgetManagerHandle phidm)
{
    Q_ASSERT(QPMock::getSingleton()->isConnected());
    QPMock::getSingleton()->setConnected(false);
    return 0;
}

// Asserts we are not connected
int CPhidgetManager_delete(CPhidgetManagerHandle phidm)
{
    // Force code to close connections before deleting
     Q_ASSERT(!QPMock::getSingleton()->isConnected());
    return 0;
}

// Stores for later reuse
int CPhidgetManager_set_OnAttach_Handler(CPhidgetManagerHandle phidm, int (*fptr)(CPhidgetHandle, void *), void *userPtr)
{
    return QPMock::getSingleton()->appendAttachListener(phidm, fptr, userPtr);
}

// Stores for later reuse
int CPhidgetManager_set_OnDetach_Handler(CPhidgetManagerHandle phidm, int (*fptr)(CPhidgetHandle, void *), void *userPtr)
{
    return QPMock::getSingleton()->appendDetachListener(phidm, fptr, userPtr);
}

int CPhidgetManager_getAttachedDevices(CPhidgetManagerHandle phidm, CPhidgetHandle *phidArray[], int *count)
{
    return QPMock::getSingleton()->getAttachedDevices(phidm, phidArray, count);
}


int CPhidgetManager_freeAttachedDevicesArray(CPhidgetHandle phidArray[])
{
    delete [] phidArray;
    return 0;
}

// Stores for later reuse
int CPhidgetManager_set_OnError_Handler(CPhidgetManagerHandle phidm, int (*fptr)(CPhidgetManagerHandle, void *, int, const char *), void *userPtr)
{
    QPMock::getSingleton()->appendErrorListener(phidm, fptr, userPtr);
    return 0;
}


int CPhidget_enableLogging(CPhidgetLog_level level, const char *outputFile)
{
    return 0;
}


int CPhidget_getDeviceClass(CPhidgetHandle phid, CPhidget_DeviceClass *deviceClass)
{
    QSharedPointer<IMockDevice> device = **phid;
    if (device) {
        *deviceClass = device->deviceClass();
        return 0;
    }
    return 1;
}


int CPhidgetInterfaceKit_create(CPhidgetInterfaceKitHandle *phid)
{
    *phid = (CPhidgetInterfaceKitHandle)QPMock::getSingleton()->getMockOfClass(PHIDCLASS_INTERFACEKIT);
    return 0;
}


int CPhidgetInterfaceKit_set_OnInputChange_Handler(CPhidgetInterfaceKitHandle phid, int (*fptr)(CPhidgetInterfaceKitHandle, void *, int, int), void *userPtr)
{

    QSharedPointer<QPMock888Device> ifkDevice = (**phid).dynamicCast<QPMock888Device>();
    if (ifkDevice) {
        ifkDevice->setOnInputChange(phid, fptr, userPtr);
        return 0;
    }
    return 1;
}

int CPhidgetInterfaceKit_set_OnOutputChange_Handler(CPhidgetInterfaceKitHandle phid, int ( *fptr)(CPhidgetInterfaceKitHandle phid, void *userPtr, int index, int outputState), void *userPtr)
{
    QSharedPointer<QPMock888Device> ifkDevice = (**phid).dynamicCast<QPMock888Device>();
    if (ifkDevice) {
        ifkDevice->setOnOutputChange(phid, fptr, userPtr);
        return 0;
    }
    return 1;
}

int CPhidgetInterfaceKit_setOutputState(CPhidgetInterfaceKitHandle phid, int index, int outputState)
{
    QSharedPointer<QPMock888Device> ifkDevice = (**phid).dynamicCast<QPMock888Device>();
    if (ifkDevice) {
        return ifkDevice->setOutput(index, outputState);
    }
    return 1;
}

int CPhidget_set_OnDetach_Handler(CPhidgetHandle phid, int (*fptr)(CPhidgetHandle, void *), void *userPtr)
{
    QSharedPointer<QPMockDevice> device = (**phid).dynamicCast<QPMock888Device>();
    if (device) {
        device->setDetachListener(fptr, userPtr);
        return 0;
    }
    return 1;
}


int CPhidget_set_OnAttach_Handler(CPhidgetHandle phid, int (*fptr)(CPhidgetHandle, void *), void *userPtr)
{
    QSharedPointer<QPMockDevice> device = (**phid).dynamicCast<QPMockDevice>();;
    if (device) {
        device->setAttachListener(fptr, userPtr);
        return 0;
    }
    return 1;
}
