#include "UnattachedMockDevice.h"

UnattachedMockDevice::UnattachedMockDevice(CPhidget_DeviceClass deviceClass, qint32 id) :
    mClass(deviceClass),
    mId(id)
{
}

UnattachedMockDevice::~UnattachedMockDevice()
{

}

qint32 UnattachedMockDevice::id() const
{
    return mId;
}

CPhidget_DeviceClass UnattachedMockDevice::deviceClass() const
{
    return mClass;
}

QList<IMockDevice::ConnectEvent> UnattachedMockDevice::attachHandlers()
{
    return mAttachHandlers;
}

void UnattachedMockDevice::setAttachHandlers(QList<IMockDevice::ConnectEvent> attachHandlers)
{
    mAttachHandlers = attachHandlers;
}

QList<IMockDevice::ConnectEvent> UnattachedMockDevice::detachHandlers()
{
    return mDetachHandlers;
}

void UnattachedMockDevice::setDetachHandlers(QList<IMockDevice::ConnectEvent> detachHandlers)
{
    mDetachHandlers = detachHandlers;
}
