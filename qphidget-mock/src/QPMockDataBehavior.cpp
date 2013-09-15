#include "QPMockDataBehavior.h"

class QPMockDataBehaviorPrivate {

public:
    QPMockDataBehavior *self;

    void doUpdate(QPMockBehaviorContext *context) {

    }
};

QPMockDataBehavior::QPMockDataBehavior(QObject *parent) :
    QPMockBehaviorDelegate(parent),
    p(new QPMockDataBehaviorPrivate)
{
    p->self = this;
}

QPMockDataBehavior::~QPMockDataBehavior()
{

}

void QPMockDataBehavior::doUpdate(QPMockBehaviorContext *context)
{
    p->doUpdate(context);
}
