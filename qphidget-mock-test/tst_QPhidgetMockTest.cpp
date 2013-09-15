#include <QString>
#include <QtTest>

#include "QPTestBehavior.h"
#include "QPMockBehavior.h"

class QPhidgetMockTest : public QObject
{
    Q_OBJECT

public:
    QPhidgetMockTest();

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

    void testInit_data() {
        QTest::addColumn<QString>("data");
        QTest::newRow("0") << QString("foo");
    }
};

QPhidgetMockTest::QPhidgetMockTest()
{
}

QTEST_APPLESS_MAIN(QPhidgetMockTest)

#include "tst_QPhidgetMockTest.moc"
