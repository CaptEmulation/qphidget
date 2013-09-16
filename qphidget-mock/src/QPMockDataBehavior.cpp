#include "QPMockDataBehavior.h"


class QPMockDataBehaviorPrivate {

public:
    QPMockDataBehavior *self;
    QVariantMap mData;
    QPMockDevice *mDevice;
    QTime mUpdateTime;

    QVariantMap data() {
        return mData;
    }

    void loadData(QVariantMap data) {
        QVariant vTime = data["time"];
        if (vTime.canConvert(QVariant::Int)) {
            mUpdateTime = QTime(0, 0).addMSecs(vTime.toInt());
            self->setNextTimeChange(mUpdateTime);
        }
    }

    void setData(QVariantMap data) {
        if (data != mData) {
            mData = data;
            loadData(data);
            emit self->dataChanged(data);
        }
    }

    QPMockDevice *device() {
        return mDevice;
    }

    void setDevice(QPMockDevice *device) {
        if (device != mDevice) {
            mDevice = device;
            emit self->deviceChanged(device);
        }
    }

    void doUpdate(QPMockUpdateContext *context) {
        Q_UNUSED(context)
        device()->setData(data());
    }
};

QPMockDataBehavior::QPMockDataBehavior(QObject *parent) :
    QPMockUpdateDelegate(parent),
    p(new QPMockDataBehaviorPrivate)
{
    p->self = this;
}

QPMockDataBehavior::~QPMockDataBehavior()
{

}

QVariantMap QPMockDataBehavior::data()
{
    return p->data();
}

QPMockDevice *QPMockDataBehavior::device()
{
    return p->device();
}

void QPMockDataBehavior::setData(QVariantMap data)
{
    p->setData(data);
}

void QPMockDataBehavior::setDevice(QPMockDevice *device)
{
    p->setDevice(device);
}

void QPMockDataBehavior::doUpdate(QPMockUpdateContext *context)
{
    p->doUpdate(context);
}
