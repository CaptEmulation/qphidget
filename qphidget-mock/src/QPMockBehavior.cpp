#include "QPMockBehavior.h"

class QPMockBehaviorPrivate {
public:

    QPMockBehavior *self;

    QTime mCurrentTime;
    qint32 mTickMs;
};

QPMockBehavior::QPMockBehavior(QObject *parent)
    : QObject(parent),
      p(new QPMockBehaviorPrivate)
{
    p->self = this;
    p->mTickMs = 0;
}

QPMockBehavior::~QPMockBehavior()
{

}

QTime QPMockBehavior::currentTime() const
{
    return p->mCurrentTime;
}

qint32 QPMockBehavior::tick()
{
    return p->mTickMs;
}

void QPMockBehavior::setTick(qint32 mseconds)
{
    if (p->mTickMs != mseconds) {
        p->mTickMs = mseconds;
        emit tickChanged(mseconds);
    }
}

void QPMockBehavior::setCurrentTime(QTime time)
{
    if(p->mCurrentTime != time) {
        p->mCurrentTime = time;
        emit currentTimeChanged(time);
    }
}
