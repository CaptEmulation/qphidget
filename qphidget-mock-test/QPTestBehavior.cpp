#include "QPTestBehavior.h"

class QPTestBehaviorPrivate {
public:

    QPTestBehavior *self;
    bool mWasUpdated;
    QList<QPMockBehaviorContext *> mContexts;

    void triggerUpated() {
        if (!mWasUpdated) {
            mWasUpdated = true;
            emit self->wasUpdatedChanged();
        }
    }

    void doUpdate(QPMockBehaviorContext *context) {
        triggerUpated();
        mContexts.append(context);
        self->contextsChanged(mContexts);
    }
};

QPTestBehavior::QPTestBehavior(QObject *parent) :
    QPMockBehaviorDelegate(parent),
    p(new QPTestBehaviorPrivate)
{
    p->self = this;
    p->mWasUpdated = false;
}

QPTestBehavior::~QPTestBehavior()
{

}

bool QPTestBehavior::wasUpdated()
{
    return p->mWasUpdated;
}

QList<QPMockBehaviorContext *> QPTestBehavior::contexts()
{
    return p->mContexts;
}

void QPTestBehavior::doUpdate(QPMockBehaviorContext *context)
{
    p->doUpdate(context);
}
