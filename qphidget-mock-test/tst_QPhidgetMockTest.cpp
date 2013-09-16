#include <QString>
#include <QtTest>
#include <QVariantMap>
#include <QBitArray>

#include "QPMock.h"
#include "QPTestBehavior.h"
#include "QPMockBehavior.h"
#include "QPMockDataBehavior.h"
#include "QPMock888Device.h"
#include "QP888Device.h"

class QPhidgetMockTest : public QObject
{
    Q_OBJECT

public:
    QPhidgetMockTest();

    const bool state1[8] = { true, false, true, false, true, false, true, false };
    const bool state2[8] = { true, true, true, true, false, false, false, false };

private Q_SLOTS:
    void initTestCase() {

    }

    void cleanupTestCase() {

    }

    void testInit() {
        QTime now = QTime::currentTime();

        QScopedPointer<QPMockBehavior> behavior(new QPMockBehavior());
        QVERIFY(behavior);

        QCOMPARE(behavior->currentTime(), QTime(0, 0));
    }

    void testAddBehavior() {
        QScopedPointer<QPTestBehavior> testBehavior(new QPTestBehavior);
        QScopedPointer<QPMockBehavior> behavior(new QPMockBehavior());

        behavior->addBehavior(testBehavior.data());
        QCOMPARE(behavior->behaviors().length(), 1);
    }

    void testUpdateBehavior() {
        QScopedPointer<QPTestBehavior> testBehavior(new QPTestBehavior);
        QScopedPointer<QPMockBehavior> behavior(new QPMockBehavior());
        testBehavior->setNextTimeChange(QTime(0,1));
        behavior->addBehavior(testBehavior.data());
        behavior->setCurrentTime(QTime(0,2));

        QVERIFY(testBehavior->wasUpdated());
        QCOMPARE(testBehavior->contexts().length(), 1);
    }

    void testDataBehavior() {
        QFETCH(QVariantMap, data);
        QFETCH(QBitArray, expected);

        QFETCH(qint32, ticks);
        QScopedPointer<QPMockBehavior> behavior(new QPMockBehavior);
        QScopedPointer<QPMockDataBehavior> dataBehavior(new QPMockDataBehavior);
        QScopedPointer<QPMock888Device> mockDevice(new QPMock888Device);
        dataBehavior->setDevice(mockDevice.data());
        dataBehavior->setData(data);
        behavior->addBehavior(dataBehavior.data());
        behavior->setTickMs(1000);

        QScopedPointer<QP888Device> device(new QP888Device());
        device->open();
        mockDevice->attach();

        for (int i = 0; i < ticks; i++) {
            behavior->tick();
        }

        for(int i = 0; i < device->inputs().length(); i++) {
            QCOMPARE(device->inputs().at(i)->state(), expected.at(i));
        }

    }

    QVariantMap setDevice888Data(const bool *bits) {
        QVariantMap data;
        for (int i = 0; i < 8; i++) {
            data[QString("%1").arg(i)] = bits[i];
        }
        return data;
    }

    QBitArray device888Results(const bool *bits) {
        QBitArray bitArray(8);
        for (int i = 0; i < 8; i ++) {
            bitArray.setBit(i, bits[i]);
        }
        return bitArray;
    }

    void testDataBehavior_data() {
        QTest::addColumn<QVariantMap>("data");
        QTest::addColumn<QBitArray>("expected");
        QTest::addColumn<qint32>("ticks");
        QVariantMap single;
        single["time"] = 1000;
        single["digital"] = setDevice888Data(state1);
        QVariantMap many;
        many["time"] = 100000;
        many["digital"] = setDevice888Data(state2);
        QTest::newRow("Single tick") << single << device888Results(state1) << 1;
        QTest::newRow("Many ticks") << many << device888Results(state2) << 100;
    }

private:
    QPMock mock;
};

QPhidgetMockTest::QPhidgetMockTest()
{
}

QTEST_APPLESS_MAIN(QPhidgetMockTest)

#include "tst_QPhidgetMockTest.moc"
