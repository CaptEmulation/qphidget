#ifndef WEBAPPCONTROLLER_H
#define WEBAPPCONTROLLER_H

#include <QObject>
#include <QScopedPointer>

#include "WebAppUriHandler.h"
#include "WebAppResponse.h"

class WebAppControllerPrivate;

class WebAppController : public QObject
{
    Q_OBJECT

    friend class WebAppControllerPrivate;
public:
    explicit WebAppController(qint16 port, QObject *parent = 0);
    ~WebAppController();

    void addHandler(WebAppUriHandler *handler, QString resource);

    WebAppResponse *handleRequest(WebAppRequest *request);

signals:
    void responseReady(WebAppResponse *response);
    void requestDataReady(WebAppRequest *request);

private slots:
    void acceptData(QTcpSocket *socket);
    void clientFinished();

private:
    QScopedPointer<WebAppControllerPrivate> p;
};

#endif // WEBAPPCONTROLLER_H
