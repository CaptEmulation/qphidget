#ifndef TST_WEBAPPCONTROLLERTEST_H
#define TST_WEBAPPCONTROLLERTEST_H

#include <QObject>
#include <QTest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSignalSpy>
#include "WebAppController.h"
#include "WebAppUriHandler.h"

class FooUriHandler : public WebAppUriHandler {
    Q_OBJECT

public:
    explicit FooUriHandler(QObject *parent = 0);

    void handleRequest(WebAppRequest *request) {
        QTextStream os(request->socket());
        os << "foo received";
        request->socket()->close();
    }

};

class PutUriHandler : public WebAppUriHandler {
    Q_OBJECT

public:
    explicit PutUriHandler(QObject *parent = 0);

    QString mRequest;

    void handleRequest(WebAppRequest *request) {
        connect(request->socket(), SIGNAL(disconnected()), this, SLOT(finished()));
    }

public slots:
    void readRequest(WebAppRequest *request) {
        QString data;
        data = request->socket()->readAll();
        mRequest = mRequest.append(data);

        if (request->socket()->atEnd()) {
            request->socket()->close();
        }
    }

    void finished() {

    }
};

class WebAppControllerTest : public QObject
{
    Q_OBJECT
public:
    explicit WebAppControllerTest(QObject *parent = 0);


private:
    qint16 mPort;

    QNetworkAccessManager mQnam;

    QString getBaseUrl() {
        return QString("http://127.0.0.1:").append(QString::number(mPort));
    }

signals:

private slots:

    void initTestCase() {
        mPort = 12543;
    }

    void testSanity() {
        WebAppController *controller = new WebAppController(8080, this);
        QVERIFY2(controller, "Does not exist");
        controller->deleteLater();
    }

    void testAddHandlerAddsAPI() {
        WebAppController *controller = new WebAppController(mPort, this);
        FooUriHandler *handler = new FooUriHandler(this);
        controller->addHandler(handler, "foo");

        QNetworkReply *reply = mQnam.get(QNetworkRequest(getBaseUrl().append("/foo")));
        QSignalSpy replyFinishedSpy(reply, SIGNAL(finished()));
        QSignalSpy webAppFinishedSpy(controller, SIGNAL(responseReady(WebAppResponse*)));
        QTRY_VERIFY(replyFinishedSpy.count());
        QTRY_VERIFY(webAppFinishedSpy.count());
        controller->deleteLater();
        handler->deleteLater();
        reply->deleteLater();
    }

    void testPutHandler () {
        WebAppController *controller = new WebAppController(++mPort, this);
        PutUriHandler *handler = new PutUriHandler(this);
        connect(controller, SIGNAL(requestDataReady(WebAppRequest*)), handler, SLOT(readRequest(WebAppRequest*)));
        QNetworkRequest request(getBaseUrl().append("/foo"));
        controller->addHandler(handler, "foo");
        QByteArray string = "bar";
        QByteArray postDataSize = QByteArray::number(string.size());
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setHeader(QNetworkRequest::ContentLengthHeader, postDataSize);
        QNetworkReply *reply = mQnam.put(request, string);
        QSignalSpy replyFinishedSpy(reply, SIGNAL(finished()));

        QTRY_VERIFY(replyFinishedSpy.count());
        QVERIFY2(handler->mRequest.indexOf("bar") != -1, "Posted text not found in request");

        controller->deleteLater();
        handler->deleteLater();
        reply->deleteLater();
    }
};

#endif // TST_WEBAPPCONTROLLERTEST_H
