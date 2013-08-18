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


#include <QString>
#include <QtTest>

#include "mock/QPMockDevice.h"
#include "mock/QPMock888Device.h"
#include "phidget21.h"
#include "mock/QPMock.h"
#include "QP888Device.h"
#include "QPInterfaceKitFactory.h"

class PhidgetTest : public QObject
{
    Q_OBJECT
    
public:
    PhidgetTest();
    
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void sanityTest();

    void device888ListensToInput() {
        QP888Device *device = ikFactory->getDevice();
        for(int i = 0; i < 8; i++) {
            QCOMPARE(device->getInput(i), false);
            mock888Device->setInput(i, i % 2 == 1);
            QCOMPARE(device->getInput(i), i % 2 == 1);
        }
    }

    void device888InputsExist() {
        QP888Device *device = ikFactory->getDevice();
        QCOMPARE(device->inputs().length(), 8);
        QCOMPARE(device->outputs().length(), 8);
    }

private:
    QPMock mock;
    QPMock888Device *mock888Device;
    QPManager *manager;
    QPInterfaceKitFactory *ikFactory;
};

PhidgetTest::PhidgetTest()
{
}

void PhidgetTest::initTestCase()
{
    qRegisterMetaType<CPhidgetHandle>();
    manager = new QPManager(this);
    ikFactory = new QPInterfaceKitFactory(this);
    manager->addDeviceInterface(PHIDCLASS_INTERFACEKIT, ikFactory);
    QSignalSpy spy(manager, SIGNAL(deviceAttached(CPhidgetHandle)));
    manager->open();
    QCOMPARE(spy.count(), 0);
    mock888Device = new QPMock888Device(this);
    QCOMPARE(spy.count(), 1);
    QList<QVariant> arguments = spy.takeFirst(); // take the first signal
    QCOMPARE(arguments.at(0).value<CPhidgetHandle>(), mock888Device); // verify the first argument
}

void PhidgetTest::cleanupTestCase()
{

}

void PhidgetTest::sanityTest()
{
    QP888Device *device = new QP888Device(this);
    QVERIFY2(device, "Failure");
}


QTEST_APPLESS_MAIN(PhidgetTest)

#include "tst_Phidget.moc"
