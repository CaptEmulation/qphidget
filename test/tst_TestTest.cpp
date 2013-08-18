#include <QString>
#include <QtTest>

class TestTest : public QObject
{
    Q_OBJECT
    
public:
    TestTest();
    
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
};

TestTest::TestTest()
{
}

void TestTest::initTestCase()
{
}

void TestTest::cleanupTestCase()
{
}

void TestTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TestTest)

#include "tst_TestTest.moc"
