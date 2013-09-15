#include "QPMockBehavior.h"

class QPMockBehaviorPrivate {
public:

    QPMockBehavior *self;

    QTime mCurrentTime;
    qint32 mTickMs;
    QList<QPMockBehaviorDelegate *> mBehaviors;

    void addBehavior(QPMockBehaviorDelegate *behavior) {
        mBehaviors.append(behavior);
    }

    void setCurrentTime(QTime time) {
        if(mCurrentTime != time) {
            mCurrentTime = time;
            emit self->currentTimeChanged(time);

            checkForUpdates();
        }
    }

    void checkForUpdates() {
        foreach(QPMockBehaviorDelegate *delegate, mBehaviors) {
            if (delegate->nextTimeChange() < mCurrentTime) {
                delegate->setNextTimeChange(mCurrentTime);
                delegate->update(Q_NULLPTR);
            }
        }
    }
};

QPMockBehavior::QPMockBehavior(QObject *parent)
    : QObject(parent),
      p(new QPMockBehaviorPrivate)
{
    p->self = this;
    p->mTickMs = 0;
    p->mCurrentTime.setHMS(0, 0, 0, 0);
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

QList<QPMockBehaviorDelegate *> QPMockBehavior::behaviors()
{
    return p->mBehaviors;
}

void QPMockBehavior::addBehavior(QPMockBehaviorDelegate *behavior)
{
    p->addBehavior(behavior);
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
    p->setCurrentTime(time);
}
