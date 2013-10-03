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

#include "QPMockHandle.h"
#include "QPMockDevice.h"
#include "QPMock888Device.h"
#include "phidget21.h"
#include "QPMock.h"
#include "QP888Device.h"
#include "QPInterfaceKitFactory.h"
#include "QPMockFactory.h"

class PhidgetTest : public QObject
{
    Q_OBJECT
    
public:
    PhidgetTest();
    ~PhidgetTest();
    
private:
    QScopedPointer<QPMockFactory> mFactory;

private Q_SLOTS:
    void initTestCase() {
        qRegisterMetaType<CPhidgetHandle>();
        mFactory.reset(new QPMockFactory);
    }

    void cleanupTestCase() {

    }

    void cleanup() {
        QPMock::getSingleton()->reset();
    }

    void sanityTest() {
        QScopedPointer<QPManager> manager(new QPManager);
        QScopedPointer<QPInterfaceKitFactory> ikFactory(new QPInterfaceKitFactory);
        manager->addDeviceInterface(PHIDCLASS_INTERFACEKIT, ikFactory.data());
        QSignalSpy spy(manager.data(), SIGNAL(deviceAttached(CPhidgetHandle)));
        manager->open();

        QCOMPARE(spy.count(), 0);
        QPMock888Device *mock888Device = mFactory->ifk888();
        mock888Device->attach();
        QCOMPARE(spy.count(), 1);
        QList<QVariant> arguments = spy.takeFirst(); // take the first signal
        QCOMPARE((**arguments.at(0).value<CPhidgetHandle>()).data(), mock888Device); // verify the first argument

    }

    void testEarlyDevice() {
        mFactory->create();
        QScopedPointer<QP888Device> device(new QP888Device());
        device->open();
        QVERIFY2(!device->connected(), "device is not yet connected");
    }

    void make888DeviceConnectionTest() {
        QScopedPointer<QP888Device> device(new QP888Device());
        QPMock888Device *mockDevice = mFactory->ifk888();
        QVERIFY2(!device.isNull(), "Device should exist");
        QVERIFY2(!device->connected(),  "Device should not be connected, it has not been opened or attached");
        device->open();
        QVERIFY2(!device->connected(),  "Device should not be connected, it has not been attached");
        mockDevice->attach();
        QVERIFY2(device->connected(),  "Device has been opened and attached, it should be connected");
    }

    void device888ListensToInput() {
        QScopedPointer<QP888Device> device(new QP888Device());
        QPMock888Device *mockDevice = mFactory->ifk888();
        device->open();
        mockDevice->attach();

        for(int i = 0; i < 8; i++) {
            QCOMPARE(device->getInput(i), false);
            mockDevice->setInput(i, i % 2 == 1);
            QCOMPARE(device->getInput(i), i % 2 == 1);
        }
    }

    void device888InputsExist() {
        QScopedPointer<QP888Device> device(new QP888Device());
        QCOMPARE(device->inputs().length(), 8);
        QCOMPARE(device->outputs().length(), 8);
    }

private:
};

PhidgetTest::PhidgetTest()
{
}

PhidgetTest::~PhidgetTest()
{
}

QTEST_APPLESS_MAIN(PhidgetTest)

#include "tst_Phidget.moc"
