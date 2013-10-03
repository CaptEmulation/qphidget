#include "QPMockBehaviorFactory.h"

QPMockBehaviorFactory::QPMockBehaviorFactory(QObject *parent) :
    QObject(parent)
{
}

QPMockBehavior *QPMockBehaviorFactory::createBehavior(QPMockDevice *device, QVariantList behaviors)
{

}
