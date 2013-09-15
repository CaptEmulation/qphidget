#include "QPMockBehaviorDelegate.h"


class QPMockBehaviorDelegatePrivate {
public:

    QPMockBehaviorDelegate *self;

    QTime mNextTimeChange;
};

QPMockBehaviorDelegate::QPMockBehaviorDelegate(QObject *parent)
    : QObject(parent),
      p(new QPMockBehaviorDelegatePrivate)
{
    p->self = this;
}

QPMockBehaviorDelegate::~QPMockBehaviorDelegate()
{

}

QTime QPMockBehaviorDelegate::nextTimeChange() const
{
    return p->mNextTimeChange;
}

void QPMockBehaviorDelegate::update(QPMockBehaviorContext *context)
{
    doUpdate(context);
}

void QPMockBehaviorDelegate::setNextTimeChange(QTime time)
{
    if(p->mNextTimeChange != time) {
        p->mNextTimeChange = time;
        emit nextTimeChangeChanged(time);
    }
}
