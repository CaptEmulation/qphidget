#ifndef PHIDGET21_TYPES_H
#define PHIDGET21_TYPES_H

#include <QWeakPointer>

class QPMock;
class IMockDevice;

typedef QWeakPointer<IMockDevice> *QPMockDeviceHandle;

/**
 * A phidget handle.
 */
typedef QPMockDeviceHandle CPhidgetHandle;

/**
 * A Phidget Manager handle.
 */
class QPMock;
typedef QPMock *CPhidgetManagerHandle;

// Typedef to phidget handle type
typedef QPMockDeviceHandle CPhidgetInterfaceKitHandle;

#endif // PHIDGET21_TYPES_H
