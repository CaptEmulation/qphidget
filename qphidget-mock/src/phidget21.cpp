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
#include "QPMock888Device.h"

#include <QMap>


int CPhidget_open(CPhidgetHandle phid, int serialNumber)
{
    return 0;
}

int CPhidget_close(CPhidgetHandle phid)
{
    // do nothing
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
    QPMock::singleton->setConnected(true);
    return 0;
}

// Asserts we are connected
int CPhidgetManager_open(CPhidgetManagerHandle phidm)
{
    Q_ASSERT(QPMock::singleton->isConnected());
    return 0;
}

// Asserts we are connected
int CPhidgetManager_close(CPhidgetManagerHandle phidm)
{
    Q_ASSERT(QPMock::singleton->isConnected());
    QPMock::singleton->setConnected(false);
    return 0;
}

// Asserts we are not connected
int CPhidgetManager_delete(CPhidgetManagerHandle phidm)
{
    // Force code to close connections before deleting
     Q_ASSERT(!QPMock::singleton->isConnected());
    return 0;
}

// Stores for later reuse
int CPhidgetManager_set_OnAttach_Handler(CPhidgetManagerHandle phidm, int (*fptr)(CPhidgetHandle, void *), void *userPtr)
{
    return QPMock::singleton->appendAttachListener(phidm, fptr, userPtr);
}

// Stores for later reuse
int CPhidgetManager_set_OnDetach_Handler(CPhidgetManagerHandle phidm, int (*fptr)(CPhidgetHandle, void *), void *userPtr)
{
    return QPMock::singleton->appendDetachListener(phidm, fptr, userPtr);
}

int CPhidgetManager_getAttachedDevices(CPhidgetManagerHandle phidm, CPhidgetHandle *phidArray[], int *count)
{
    return QPMock::singleton->getAttachedDevices(phidm, phidArray, count);
}


int CPhidgetManager_freeAttachedDevicesArray(CPhidgetHandle phidArray[])
{
    delete [] phidArray;
    return 0;
}

// Stores for later reuse
int CPhidgetManager_set_OnError_Handler(CPhidgetManagerHandle phidm, int (*fptr)(CPhidgetManagerHandle, void *, int, const char *), void *userPtr)
{
    QPMock::singleton->appendErrorListener(phidm, fptr, userPtr);
    return 0;
}


int CPhidget_enableLogging(CPhidgetLog_level level, const char *outputFile)
{
    return 0;
}


int CPhidget_getDeviceClass(CPhidgetHandle phid, CPhidget_DeviceClass *deviceClass)
{
    *deviceClass = phid->deviceClass();
    return 0;
}


int CPhidgetInterfaceKit_create(CPhidgetInterfaceKitHandle *phid)
{
    *phid = (CPhidgetInterfaceKitHandle)QPMock::singleton->getMockOfClass(PHIDCLASS_INTERFACEKIT);
    return 0;
}


int CPhidgetInterfaceKit_set_OnInputChange_Handler(CPhidgetInterfaceKitHandle phid, int (*fptr)(CPhidgetInterfaceKitHandle, void *, int, int), void *userPtr)
{
    phid->setOnInputChange(fptr, userPtr);
    return 0;
}


int CPhidgetInterfaceKit_setOutputState(CPhidgetInterfaceKitHandle phid, int index, int outputState)
{
    return phid->setOutput(index, outputState);
}


int CPhidget_set_OnDetach_Handler(CPhidgetHandle phid, int (*fptr)(CPhidgetHandle, void *), void *userPtr)
{

    phid->setDetachListener(fptr, userPtr);
    return 0;
}


int CPhidget_set_OnAttach_Handler(CPhidgetHandle phid, int (*fptr)(CPhidgetHandle, void *), void *userPtr)
{
    phid->setAttachListener(fptr, userPtr);
    return 0;
}
