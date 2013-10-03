#ifndef IMOCKDEVICE_H
#define IMOCKDEVICE_H

#include <QObject>
#include "phidget21.h"

class IMockDevice
{
public:
    virtual ~IMockDevice();

    struct ConnectEvent {
        DeviceCallback fptr;
        void *userPtr;
    };

    virtual qint32 id() const = 0;

    virtual CPhidget_DeviceClass deviceClass() const = 0;

};

Q_DECLARE_INTERFACE(IMockDevice, "com.captemulation.phidget.mock.device/1.0")

#endif // IMOCKDEVICE_H
