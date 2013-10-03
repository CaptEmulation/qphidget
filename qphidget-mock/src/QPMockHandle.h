#ifndef QPMOCKHANDLE_H
#define QPMOCKHANDLE_H

#include "IMockDevice.h"

#include <QScopedPointer>
#include <QWeakPointer>

class QPMockHandlePrivate;

class QPMockHandle
{
public:
    QPMockHandle(IMockDevice *mock);
    ~QPMockHandle();
    QPMockHandle(QPMockHandle const &other);

    QSharedPointer<IMockDevice> operator*() const;
    QPMockHandle &operator=(IMockDevice * const &mock);
    void reset(IMockDevice *mock);

private:
    QScopedPointer<QPMockHandlePrivate> p;
};

Q_DECLARE_METATYPE(CPhidgetHandle)

#endif // QPMOCKHANDLE_H
