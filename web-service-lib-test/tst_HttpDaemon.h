#ifndef TST_HTTPDAEMON_H
#define TST_HTTPDAEMON_H

#include <QObject>


#include <QString>
#include <QtTest>

#include "HttpDaemon.h"
#include <QCoreApplication>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QTcpSocket>

class HttpDaemonTest : public QObject
{
    Q_OBJECT

public:
    HttpDaemonTest();

    HttpDaemon *mDaemon;
    qint16 mPort;
    QNetworkAccessManager mQnam;

    QString getBaseUrl() {
        return QString("http://127.0.0.1:").append(QString::number(mPort));
    }

signals:
    void testEnd();

public slots:
    void readData(QTcpSocket *socket) {
        socket->close();
    }

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void sanity();
    void sanity_data();

    void socketTest() {
        connect(mDaemon, SIGNAL(readData(QTcpSocket*)), this, SLOT(readData(QTcpSocket*)));
        QNetworkReply *reply = mQnam.get(QNetworkRequest(getBaseUrl()));
        QSignalSpy spy(reply, SIGNAL(finished()));
        QTRY_VERIFY(spy.count());
        reply->deleteLater();
        disconnect(mDaemon, SIGNAL(readData(QTcpSocket*)), this, SLOT(readData(QTcpSocket*)));
    }


};



#endif // TST_HTTPDAEMON_H
