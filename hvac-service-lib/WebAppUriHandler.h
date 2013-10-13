#ifndef WEBAPPURIHANDLER_H
#define WEBAPPURIHANDLER_H

#include <QObject>
#include "WebAppResponse.h"
#include "WebAppRequest.h"

class WebAppUriHandlerPrivate;

class WebAppUriHandler : public QObject
{
    Q_OBJECT
public:
    explicit WebAppUriHandler(QObject *parent = 0);
    ~WebAppUriHandler();

    //void addHandler(WebAppUriHandler *handler, QString resource);

    virtual void handleRequest(WebAppRequest *request);

signals:

public slots:

private:
    QScopedPointer<WebAppUriHandlerPrivate> p;
};

#endif // WEBAPPURIHANDLER_H
