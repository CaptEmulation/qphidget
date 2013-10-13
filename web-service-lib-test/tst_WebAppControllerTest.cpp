#include "tst_WebAppControllerTest.h"

WebAppControllerTest::WebAppControllerTest(QObject *parent) :
    QObject(parent)
{

}


FooUriHandler::FooUriHandler(QObject *parent) :
    WebAppUriHandler(parent)
{

}


PutUriHandler::PutUriHandler(QObject *parent) :
    WebAppUriHandler(parent)
{

}
