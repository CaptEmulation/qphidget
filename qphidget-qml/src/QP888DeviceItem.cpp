#include "QP888DeviceItem.h"
#include "QP888Device.h"

class QP888DeviceItemPrivate
{
public:
    QP888DeviceItem* self;
    QP888Device *mDevice;

    void initialize() {
        mDevice = new QP888Device(self);
        QObject::connect(mDevice, SIGNAL(connectedChanged(bool)), self, SIGNAL(connectedChanged(bool)));
        QObject::connect(mDevice->inputs().at(0), SIGNAL(stateChanged(bool)), self, SIGNAL(input0Changed(bool)));
        QObject::connect(mDevice->inputs().at(1), SIGNAL(stateChanged(bool)), self, SIGNAL(input1Changed(bool)));
        QObject::connect(mDevice->inputs().at(2), SIGNAL(stateChanged(bool)), self, SIGNAL(input2Changed(bool)));
        QObject::connect(mDevice->inputs().at(3), SIGNAL(stateChanged(bool)), self, SIGNAL(input3Changed(bool)));
        QObject::connect(mDevice->inputs().at(4), SIGNAL(stateChanged(bool)), self, SIGNAL(input4Changed(bool)));
        QObject::connect(mDevice->inputs().at(5), SIGNAL(stateChanged(bool)), self, SIGNAL(input5Changed(bool)));
        QObject::connect(mDevice->inputs().at(6), SIGNAL(stateChanged(bool)), self, SIGNAL(input6Changed(bool)));
        QObject::connect(mDevice->inputs().at(7), SIGNAL(stateChanged(bool)), self, SIGNAL(input7Changed(bool)));
        QObject::connect(mDevice->outputs().at(0), SIGNAL(stateChanged(bool)), self, SIGNAL(output0Changed(bool)));
        QObject::connect(mDevice->outputs().at(1), SIGNAL(stateChanged(bool)), self, SIGNAL(output1Changed(bool)));
        QObject::connect(mDevice->outputs().at(2), SIGNAL(stateChanged(bool)), self, SIGNAL(output2Changed(bool)));
        QObject::connect(mDevice->outputs().at(3), SIGNAL(stateChanged(bool)), self, SIGNAL(output3Changed(bool)));
        QObject::connect(mDevice->outputs().at(4), SIGNAL(stateChanged(bool)), self, SIGNAL(output4Changed(bool)));
        QObject::connect(mDevice->outputs().at(5), SIGNAL(stateChanged(bool)), self, SIGNAL(output5Changed(bool)));
        QObject::connect(mDevice->outputs().at(6), SIGNAL(stateChanged(bool)), self, SIGNAL(output6Changed(bool)));
        QObject::connect(mDevice->outputs().at(7), SIGNAL(stateChanged(bool)), self, SIGNAL(output7Changed(bool)));
        mDevice->open();
    }
};

QP888DeviceItem::QP888DeviceItem(QQuickItem *parent) :
    QQuickItem(parent),
    p(new QP888DeviceItemPrivate)
{
    p->self = this;
    p->initialize();
}

QP888DeviceItem::~QP888DeviceItem()
{
}

bool QP888DeviceItem::connected()
{
    return p->mDevice->connected();
}

bool QP888DeviceItem::input0()
{
    return p->mDevice->inputs().at(0)->state();
}

bool QP888DeviceItem::input1()
{
    return p->mDevice->inputs().at(1)->state();
}

bool QP888DeviceItem::input2()
{
    return p->mDevice->inputs().at(2)->state();
}

bool QP888DeviceItem::input3()
{
    return p->mDevice->inputs().at(3)->state();
}

bool QP888DeviceItem::input4()
{
    return p->mDevice->inputs().at(4)->state();
}

bool QP888DeviceItem::input5()
{
    return p->mDevice->inputs().at(5)->state();
}

bool QP888DeviceItem::input6()
{
    return p->mDevice->inputs().at(6)->state();
}

bool QP888DeviceItem::input7()
{
    return p->mDevice->inputs().at(7)->state();
}

bool QP888DeviceItem::output0()
{
    return p->mDevice->outputs().at(0)->state();
}

bool QP888DeviceItem::output1()
{
    return p->mDevice->outputs().at(1)->state();
}

bool QP888DeviceItem::output2()
{
    return p->mDevice->outputs().at(2)->state();
}

bool QP888DeviceItem::output3()
{
    return p->mDevice->outputs().at(3)->state();
}

bool QP888DeviceItem::output4()
{
    return p->mDevice->outputs().at(4)->state();
}

bool QP888DeviceItem::output5()
{
    return p->mDevice->outputs().at(5)->state();
}

bool QP888DeviceItem::output6()
{
    return p->mDevice->outputs().at(6)->state();
}

bool QP888DeviceItem::output7()
{
    return p->mDevice->outputs().at(7)->state();
}

void QP888DeviceItem::setOutput0(bool state)
{
    p->mDevice->outputs().at(0)->setState(state);
}

void QP888DeviceItem::setOutput1(bool state)
{
    p->mDevice->outputs().at(1)->setState(state);
}

void QP888DeviceItem::setOutput2(bool state)
{
    p->mDevice->outputs().at(2)->setState(state);
}

void QP888DeviceItem::setOutput3(bool state)
{
    p->mDevice->outputs().at(3)->setState(state);
}

void QP888DeviceItem::setOutput4(bool state)
{
    p->mDevice->outputs().at(4)->setState(state);
}

void QP888DeviceItem::setOutput5(bool state)
{
    p->mDevice->outputs().at(5)->setState(state);
}

void QP888DeviceItem::setOutput6(bool state)
{
    p->mDevice->outputs().at(6)->setState(state);
}

void QP888DeviceItem::setOutput7(bool state)
{
    p->mDevice->outputs().at(7)->setState(state);
}
