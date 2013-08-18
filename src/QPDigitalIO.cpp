/**
Copyright 2013 John Dean, III

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "QPDigitalIO.h"

#include <functional>

class QPDigitalIOPrivate
{
public:
    QPDigitalIO *self;
    bool mState;
    QPDigitalIO::Type mType;
    qint32 mIndex;

    bool state() {
        return mState;
    }

    void setState(bool state) {
        if (state != mState) {
            mState = state;
            emit self->stateChanged(state);
        }
    }
};

QPDigitalIO::QPDigitalIO(Type type, qint32 index, QObject *parent) :
    QObject(parent),
    p(new QPDigitalIOPrivate)
{
    p->self = this;
    p->mState = false;
    p->mType = type;
    p->mIndex = index;
}

QPDigitalIO::~QPDigitalIO()
{
}

bool QPDigitalIO::state()
{
    return p->state();
}


void QPDigitalIO::setState(bool state)
{
    p->setState(state);
}


