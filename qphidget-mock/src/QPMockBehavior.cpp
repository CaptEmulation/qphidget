#include "QPMockBehavior.h"

class QPMockBehaviorPrivate {
public:

    QPMockBehavior *self;

    QTime mCurrentTime;
    qint32 mTickMs;
    QList<QPMockUpdateDelegate *> mBehaviors;

    void tick() {
        setCurrentTime(mCurrentTime.addMSecs(mTickMs));
    }

    void addBehavior(QPMockUpdateDelegate *behavior) {
        mBehaviors.append(behavior);
    }

    void setCurrentTime(QTime time) {
        if(mCurrentTime != time) {
            QTime lastTime = mCurrentTime;
            mCurrentTime = time;
            emit self->currentTimeChanged(time);

            checkForUpdates(lastTime);
        }
    }

    void checkForUpdates(QTime &lastTime) {
        foreach(QPMockUpdateDelegate *delegate, mBehaviors) {
            if (delegate->nextTimeChange() <= mCurrentTime &&
                    delegate->nextTimeChange() > lastTime) {
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

void QPMockBehavior::tick()
{
    p->tick();
}

QTime QPMockBehavior::currentTime() const
{
    return p->mCurrentTime;
}

qint32 QPMockBehavior::tickMs()
{
    return p->mTickMs;
}

QList<QPMockUpdateDelegate *> QPMockBehavior::behaviors()
{
    return p->mBehaviors;
}

void QPMockBehavior::addBehavior(QPMockUpdateDelegate *behavior)
{
    p->addBehavior(behavior);
}

void QPMockBehavior::setTickMs(qint32 mseconds)
{
    if (p->mTickMs != mseconds) {
        p->mTickMs = mseconds;
        emit tickMsChanged(mseconds);
    }
}

void QPMockBehavior::setCurrentTime(QTime time)
{
    p->setCurrentTime(time);
}
