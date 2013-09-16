#include "QPTestBehavior.h"

class QPTestBehaviorPrivate {
public:

    QPTestBehavior *self;
    bool mWasUpdated;
    QList<QPMockUpdateContext *> mContexts;

    void triggerUpated() {
        if (!mWasUpdated) {
            mWasUpdated = true;
            emit self->wasUpdatedChanged();
        }
    }

    void doUpdate(QPMockUpdateContext *context) {
        triggerUpated();
        mContexts.append(context);
        self->contextsChanged(mContexts);
    }
};

QPTestBehavior::QPTestBehavior(QObject *parent) :
    QPMockUpdateDelegate(parent),
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

QList<QPMockUpdateContext *> QPTestBehavior::contexts()
{
    return p->mContexts;
}

void QPTestBehavior::doUpdate(QPMockUpdateContext *context)
{
    p->doUpdate(context);
}
