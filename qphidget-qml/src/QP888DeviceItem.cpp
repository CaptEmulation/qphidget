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
        QObject::connect(mDevice->outputs().at(0), SIGNAL(stateChanged(bool)), self, SIGNAL(output0Changed(bool)));
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

bool QP888DeviceItem::output0()
{
    return p->mDevice->outputs().at(0)->state();
}

void QP888DeviceItem::setOutput0(bool state)
{
    p->mDevice->outputs().at(0)->setState(state);
}

