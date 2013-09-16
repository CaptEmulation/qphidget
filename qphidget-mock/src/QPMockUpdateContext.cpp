#include "QPMockUpdateContext.h"

class QPMockUpdateContextPrivate {
public:
    QPMockUpdateContext *self;

    QTime mCurrentTime;
};

QPMockUpdateContext::QPMockUpdateContext(QObject *parent) :
    QObject(parent),
    p(new QPMockUpdateContextPrivate)
{
    p->self = this;
}

QPMockUpdateContext::~QPMockUpdateContext()
{

}

QTime QPMockUpdateContext::currentTime() const
{
    return p->mCurrentTime;
}

void QPMockUpdateContext::setCurrentTime(QTime time)
{
    if (p->mCurrentTime != time) {
        p->mCurrentTime = time;
        emit currentTimeChanged(time);
    }
}
