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
    void initTestCase();
    void cleanupTestCase();
    void testInit();
    void testInit_data();
};

QPhidgetMockTest::QPhidgetMockTest()
{
}

void QPhidgetMockTest::initTestCase()
{
}

void QPhidgetMockTest::cleanupTestCase()
{
}

void QPhidgetMockTest::testInit()
{
    QPMockBehavior *behavior = new QPMockBehavior(this);
    QVERIFY(behavior);
}

void QPhidgetMockTest::testInit_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString("foo");
}

QTEST_APPLESS_MAIN(QPhidgetMockTest)

#include "tst_QPhidgetMockTest.moc"
