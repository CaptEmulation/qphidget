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

/**
  * This is a test mock implementation of the Phidget API, for unit testing.
  * This is a complete reimplementation for production code.  For tests, use the mock/* classes
  * Phidget21 API Copyright by its respective owner
  */


#ifndef PHIDGET21_H
#define PHIDGET21_H

typedef enum
{
 PHIDCLASS_INTERFACEKIT = 7				/**< Phidget Interface Kit */

} CPhidget_DeviceClass;

/**
 * Phidget device id uniquely identifies a specific type of Phidget.
 */
typedef enum
{
 PHIDID_INTERFACEKIT_8_8_8 = 0x045,						/**< Phidget Interface Kit 8/8/8 (1013, 1018, 1019) */

 /* Device in firmware upgrade mode */
 PHIDID_FIRMWARE_UPGRADE = 0x098

} CPhidget_DeviceID;

     typedef enum {
 PHIDGET_LOG_CRITICAL = 1,		/**< Really important errors that can't be recovered. Usually followed by an abort() */
 PHIDGET_LOG_ERROR,			/**< Errors that are recovered from. */
 PHIDGET_LOG_WARNING,		/**< Warning's about weird things that aren't neccesarily wrong. */
 PHIDGET_LOG_DEBUG,			/**< Should only be used during development - only shows up in the debug library. */
 PHIDGET_LOG_INFO,				/**< Info about the going on's in the library. */
 PHIDGET_LOG_VERBOSE		/**< Everything, including very common messages. */
} CPhidgetLog_level;


/**
 * A phidget handle.
 */
class QPMockDevice;
typedef QPMockDevice * CPhidgetHandle;

/**
 * A Phidget Manager handle.
 */
class QPMock;
typedef QPMock *CPhidgetManagerHandle;


int CPhidget_enableLogging (CPhidgetLog_level level, const char *outputFile);


int CPhidget_open (CPhidgetHandle phid, int serialNumber);
int CPhidget_close (CPhidgetHandle phid);
int CPhidget_delete (CPhidgetHandle phid);
int CPhidget_set_OnDetach_Handler (CPhidgetHandle phid, int (__stdcall * fptr) (CPhidgetHandle phid, void *userPtr), void *userPtr);
int CPhidget_set_OnAttach_Handler (CPhidgetHandle phid, int (__stdcall * fptr) (CPhidgetHandle phid, void *userPtr), void *userPtr);



int CPhidgetManager_create (CPhidgetManagerHandle * phidm);
int CPhidgetManager_open (CPhidgetManagerHandle phidm);
int CPhidgetManager_close (CPhidgetManagerHandle phidm);
int CPhidgetManager_delete (CPhidgetManagerHandle phidm);
int CPhidgetManager_set_OnAttach_Handler (CPhidgetManagerHandle phidm, int (__stdcall * fptr) (CPhidgetHandle phid, void *userPtr), void *userPtr);
int CPhidgetManager_set_OnDetach_Handler (CPhidgetManagerHandle phidm, int (__stdcall * fptr) (CPhidgetHandle phid, void *userPtr), void *userPtr);
int CPhidgetManager_getAttachedDevices (CPhidgetManagerHandle phidm, CPhidgetHandle * phidArray[], int *count);
int CPhidgetManager_freeAttachedDevicesArray (CPhidgetHandle phidArray[]);
int CPhidgetManager_set_OnError_Handler (CPhidgetManagerHandle phidm, int (* fptr) (CPhidgetManagerHandle phidm, void *userPtr, int errorCode, const char *errorString),
                         void *userPtr);
int __stdcall CPhidget_getDeviceClass (CPhidgetHandle phid, CPhidget_DeviceClass * deviceClass);



/************************ Interface Kit mock ***********************/

class QPMock888Device;
typedef QPMock888Device *CPhidgetInterfaceKitHandle;

int CPhidgetInterfaceKit_create (CPhidgetInterfaceKitHandle * phid);
int CPhidgetInterfaceKit_setOutputState (CPhidgetInterfaceKitHandle phid, int index, int outputState);
int CPhidgetInterfaceKit_set_OnInputChange_Handler (CPhidgetInterfaceKitHandle phid, int (__stdcall * fptr) (CPhidgetInterfaceKitHandle phid, void *userPtr, int index, int inputState),
                                void *userPtr);

#endif // PHIDGET21_H
