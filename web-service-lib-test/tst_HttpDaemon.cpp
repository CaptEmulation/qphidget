#include "tst_HttpDaemon.h"

HttpDaemonTest::HttpDaemonTest()
{
}

void HttpDaemonTest::initTestCase()
{
    mPort = 12456;
    mDaemon = new HttpDaemon(mPort);
    QCoreApplication *app = QCoreApplication::instance();
    connect(this, SIGNAL(testEnd()), app, SLOT(quit()), Qt::QueuedConnection);
}

void HttpDaemonTest::cleanupTestCase()
{
    emit testEnd();
}

void HttpDaemonTest::sanity()
{
    QFETCH(QString, data);
    QVERIFY2(true, "Failure");
}

void HttpDaemonTest::sanity_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

