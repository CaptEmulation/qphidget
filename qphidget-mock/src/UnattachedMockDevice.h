#ifndef UNATTACHEDMOCKDEVICE_H
#define UNATTACHEDMOCKDEVICE_H

#include "IMockDevice.h"

class UnattachedMockDevice : public IMockDevice
{
public:
    UnattachedMockDevice(CPhidget_DeviceClass deviceClass, qint32 id = -1);
    ~UnattachedMockDevice();

    virtual qint32 id() const;

    virtual CPhidget_DeviceClass deviceClass() const;

    QList<IMockDevice::ConnectEvent> attachHandlers();
    void setAttachHandlers(QList<IMockDevice::ConnectEvent> attachHandlers);
    QList<IMockDevice::ConnectEvent> detachHandlers();
    void setDetachHandlers(QList<IMockDevice::ConnectEvent> detachHandlers);

    void setAttachListener(int (*fptr)(CPhidgetHandle, void *), void *userPtr);
    void setDetachListener(int (*fptr)(CPhidgetHandle, void *), void *userPtrk);

private:
    qint32 mId;
    CPhidget_DeviceClass mClass;
    QList<IMockDevice::ConnectEvent> mAttachHandlers;
    QList<IMockDevice::ConnectEvent> mDetachHandlers;
};

#endif // UNATTACHEDMOCKDEVICE_H
