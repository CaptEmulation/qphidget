#include "QPMockFactory.h"
#include "QPMock.h"
#include "UnattachedMockDevice.h"

class QPMockFactoryPrivate {
public:

};

QPMockFactory::QPMockFactory(QObject *parent) :
    QObject(parent),
    p(new QPMockFactoryPrivate)
{
}

QPMockFactory::~QPMockFactory()
{

}

void QPMockFactory::create()
{
    QPMock *mock = QPMock::getSingleton();
    mock->appendMock(new UnattachedMockDevice(PHIDCLASS_INTERFACEKIT, -1));
}

QPMock888Device *QPMockFactory::ifk888(qint32 id)
{
    return new QPMock888Device(id);
}
