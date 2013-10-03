#include "QPMock888DeviceItem.h"

#include "QPMock888Device.h"
#include "QPMockHandle.h"
#include "QPMock.h"

class QPMock888DeviceItemPrivate
{
public:
    QPMock888DeviceItem* self;
    QPMock888Device *mDevice;
    QPMock mMock;

    void initialize() {
        mDevice = (**QPMock::getSingleton()->getMockOfClass(PHIDCLASS_INTERFACEKIT)).dynamicCast<QPMock888Device>().data();
        if (!mDevice) {
            mDevice = new QPMock888Device(-1, self);
        }

        QObject::connect(mDevice, SIGNAL(inputChanged(int,bool)), self, SLOT(inputChanged(int,bool)));
        QObject::connect(mDevice, SIGNAL(outputChanged(int,bool)), self, SLOT(outputChanged(int,bool)));


        mDevice->attach();
    }

    void inputChanged(int index, bool input) {
        switch(index) {
        case 0:
            emit self->input0Changed(input);
            break;
        case 1:
            emit self->input1Changed(input);
            break;

        }
    }

    void outputChanged(int index, bool output) {
        switch(index) {
        case 0:
            emit self->output0Changed(output);
            break;
        case 1:
            emit self->output1Changed(output);
            break;

        }
    }
};

QPMock888DeviceItem::QPMock888DeviceItem(QQuickItem *parent) :
    QQuickItem(parent),
    p(new QPMock888DeviceItemPrivate)
{
    p->self = this;
    p->initialize();
}

QPMock888DeviceItem::~QPMock888DeviceItem()
{
}

qint32 QPMock888DeviceItem::uid()
{
    return p->mDevice->id();
}

bool QPMock888DeviceItem::connected()
{
    return p->mDevice->isAttached();
}

bool QPMock888DeviceItem::input0()
{
    return p->mDevice->input(0);
}

void QPMock888DeviceItem::setInput0(bool state)
{
    p->mDevice->setInput(0, state);
}

bool QPMock888DeviceItem::input1()
{
    return p->mDevice->input(1);
}

void QPMock888DeviceItem::setInput1(bool state)
{
    p->mDevice->setInput(1, state);
}

void QPMock888DeviceItem::inputChanged(int index, bool input)
{
    p->inputChanged(index, input);
}

void QPMock888DeviceItem::outputChanged(int index, bool output)
{
    p->outputChanged(index, output);
}

bool QPMock888DeviceItem::output0()
{
    return p->mDevice->output(0);
}

bool QPMock888DeviceItem::output1()
{
    return p->mDevice->output(1);
}

void QPMock888DeviceItem::setUid(quint32 uid)
{
    p->mDevice->setId(uid);
}


