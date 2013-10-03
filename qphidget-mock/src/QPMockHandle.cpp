#include "QPMockHandle.h"

class QPMockHandlePrivate {
public:
    QSharedPointer<IMockDevice> mPtr;
};

QPMockHandle::QPMockHandle(IMockDevice *mock) :
    p(new QPMockHandlePrivate)
{
    p->mPtr.reset(mock);
}

QPMockHandle::~QPMockHandle()
{
}

QPMockHandle::QPMockHandle(const QPMockHandle &other)
{
    p->mPtr = other.p->mPtr;
}


QSharedPointer<IMockDevice> QPMockHandle::operator*() const
{
    return p->mPtr;
}

QPMockHandle &QPMockHandle::operator=(IMockDevice * const &mock)
{
    p->mPtr.reset(mock);
    return *this;
}

void QPMockHandle::reset(IMockDevice *mock)
{
    p->mPtr = QSharedPointer<IMockDevice>(mock);
}


