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
    ~PhidgetTest();
    
private Q_SLOTS:
    void initTestCase() {
        qRegisterMetaType<CPhidgetHandle>();
    }

    void cleanupTestCase() {

    }

    void cleanup() {
        mock.reset();
    }

    void sanityTest() {
        QScopedPointer<QPManager> manager(new QPManager);
        QScopedPointer<QPInterfaceKitFactory> ikFactory(new QPInterfaceKitFactory);
        manager->addDeviceInterface(PHIDCLASS_INTERFACEKIT, ikFactory.data());
        QSignalSpy spy(manager.data(), SIGNAL(deviceAttached(CPhidgetHandle)));
        manager->open();

        QCOMPARE(spy.count(), 0);
        QScopedPointer<QPMock888Device> mock888Device(new QPMock888Device);
        mock888Device->attach();
        QCOMPARE(spy.count(), 1);
        QList<QVariant> arguments = spy.takeFirst(); // take the first signal
        QCOMPARE(arguments.at(0).value<CPhidgetHandle>(), mock888Device.data()); // verify the first argument
    }

    void make888DeviceConnectionTest() {
        QScopedPointer<QP888Device> device(new QP888Device());
        QScopedPointer<QPMock888Device> mockDevice(new QPMock888Device());
        QVERIFY2(!device.isNull(), "Device should exist");
        QVERIFY2(!device->connected(),  "Device should not be connected, it has not been opened or attached");
        device->open();
        QVERIFY2(!device->connected(),  "Device should not be connected, it has not been attached");
        mockDevice->attach();
        QVERIFY2(device->connected(),  "Device has been opened and attached, it should be connected");
    }

    void device888ListensToInput() {
        QScopedPointer<QP888Device> device(new QP888Device());
        QScopedPointer<QPMock888Device> mockDevice(new QPMock888Device());
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
    QPMock mock;
};

PhidgetTest::PhidgetTest()
{
}

PhidgetTest::~PhidgetTest()
{
}

QTEST_APPLESS_MAIN(PhidgetTest)

#include "tst_Phidget.moc"
