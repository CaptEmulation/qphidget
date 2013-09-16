#include "QPMockUpdateDelegate.h"


class QPMockUpdateDelegatePrivate {
public:

    QPMockUpdateDelegate *self;

    QTime mNextTimeChange;
};

QPMockUpdateDelegate::QPMockUpdateDelegate(QObject *parent)
    : QObject(parent),
      p(new QPMockUpdateDelegatePrivate)
{
    p->self = this;
}

QPMockUpdateDelegate::~QPMockUpdateDelegate()
{

}

QTime QPMockUpdateDelegate::nextTimeChange() const
{
    return p->mNextTimeChange;
}

void QPMockUpdateDelegate::update(QPMockUpdateContext *context)
{
    doUpdate(context);
}

void QPMockUpdateDelegate::setNextTimeChange(QTime time)
{
    if(p->mNextTimeChange != time) {
        p->mNextTimeChange = time;
        emit nextTimeChangeChanged(time);
    }
}
