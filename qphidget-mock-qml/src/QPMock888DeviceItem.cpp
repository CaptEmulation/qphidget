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
        case 2:
            emit self->input2Changed(input);
            break;
        case 3:
            emit self->input3Changed(input);
            break;
        case 4:
            emit self->input4Changed(input);
            break;
        case 5:
            emit self->input5Changed(input);
            break;
        case 6:
            emit self->input6Changed(input);
            break;
        case 7:
            emit self->input7Changed(input);
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
        case 2:
            emit self->output2Changed(output);
            break;
        case 3:
            emit self->output3Changed(output);
            break;
        case 4:
            emit self->output4Changed(output);
            break;
        case 5:
            emit self->output5Changed(output);
            break;
        case 6:
            emit self->output6Changed(output);
            break;
        case 7:
            emit self->output7Changed(output);
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

bool QPMock888DeviceItem::input1()
{
    return p->mDevice->input(1);
}

bool QPMock888DeviceItem::input2()
{
    return p->mDevice->input(2);
}

bool QPMock888DeviceItem::input3()
{
    return p->mDevice->input(3);
}

bool QPMock888DeviceItem::input4()
{
    return p->mDevice->input(4);
}

bool QPMock888DeviceItem::input5()
{
    return p->mDevice->input(5);
}

bool QPMock888DeviceItem::input6()
{
    return p->mDevice->input(6);
}

bool QPMock888DeviceItem::input7()
{
    return p->mDevice->input(7);
}

void QPMock888DeviceItem::setInput0(bool state)
{
    p->mDevice->setInput(0, state);
}


void QPMock888DeviceItem::setInput1(bool state)
{
    p->mDevice->setInput(1, state);
}

void QPMock888DeviceItem::setInput2(bool state)
{
    p->mDevice->setInput(2, state);
}

void QPMock888DeviceItem::setInput3(bool state)
{
    p->mDevice->setInput(3, state);
}

void QPMock888DeviceItem::setInput4(bool state)
{
    p->mDevice->setInput(4, state);
}

void QPMock888DeviceItem::setInput5(bool state)
{
    p->mDevice->setInput(5, state);
}

void QPMock888DeviceItem::setInput6(bool state)
{
    p->mDevice->setInput(6, state);
}

void QPMock888DeviceItem::setInput7(bool state)
{
    p->mDevice->setInput(7, state);
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

bool QPMock888DeviceItem::output2()
{
    return p->mDevice->output(2);
}

bool QPMock888DeviceItem::output3()
{
    return p->mDevice->output(3);
}

bool QPMock888DeviceItem::output4()
{
    return p->mDevice->output(4);
}

bool QPMock888DeviceItem::output5()
{
    return p->mDevice->output(5);
}

bool QPMock888DeviceItem::output6()
{
    return p->mDevice->output(6);
}

bool QPMock888DeviceItem::output7()
{
    return p->mDevice->output(7);
}

void QPMock888DeviceItem::setUid(quint32 uid)
{
    p->mDevice->setId(uid);
}


