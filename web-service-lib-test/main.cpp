
#include <QCoreApplication>
#include <QTest>
#include "tst_HttpDaemon.h"
#include "tst_WebAppControllerTest.h"

int main(int argc, char *argv[])
{
    QCoreApplication c(argc, argv);

    WebAppControllerTest webAppControllerTest;
    QTest::qExec(&webAppControllerTest, argc, argv);

    HttpDaemonTest webService;
    QTest::qExec(&webService, argc, argv);

    return c.exec();
}
