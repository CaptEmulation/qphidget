#include "QPMockBehaviorContext.h"

class QPMockBehaviorContextPrivate {
public:
    QPMockBehaviorContext *self;

    QTime mCurrentTime;
};

QPMockBehaviorContext::QPMockBehaviorContext(QObject *parent) :
    QObject(parent),
    p(new QPMockBehaviorContextPrivate)
{
    p->self = this;
}

QPMockBehaviorContext::~QPMockBehaviorContext()
{

}

QTime QPMockBehaviorContext::currentTime() const
{
    return p->mCurrentTime;
}

void QPMockBehaviorContext::setCurrentTime(QTime time)
{
    if (p->mCurrentTime != time) {
        p->mCurrentTime = time;
        emit currentTimeChanged(time);
    }
}
