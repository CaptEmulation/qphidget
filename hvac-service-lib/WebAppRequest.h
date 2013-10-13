#ifndef WEBAPPREQUEST_H
#define WEBAPPREQUEST_H

#include <QObject>
#include <QUrl>
#include <QStringList>
#include <QTcpSocket>
#include "WebAppResponse.h"

class WebAppRequestPrivate;

class WebAppRequest : public QObject
{
    Q_OBJECT
    Q_ENUMS(RequestType)
    Q_PROPERTY(RequestType requestType READ requestType WRITE setRequestType NOTIFY requestTypeChanged)
    Q_PROPERTY(QString unhandledUri READ unhandledUri WRITE setUnhandledUri NOTIFY unhandledUriChanged)
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QStringList resources READ resources WRITE setResources NOTIFY resourcesChanged)
    Q_PROPERTY(QString currentResourceName READ currentResourceName WRITE setCurrentResourceName NOTIFY currentResourceNameChanged)
    Q_PROPERTY(int currentResourceIndex READ currentResourceIndex WRITE setCurrentResourceIndex NOTIFY currentResourceIndexChanged)
    Q_PROPERTY(QTcpSocket *socket READ socket WRITE setSocket NOTIFY socketChanged)
    Q_PROPERTY(WebAppResponse * response READ response WRITE setResponse NOTIFY responseChanged)
    Q_PROPERTY(QMap<QString, QString> headers READ headers)
    Q_PROPERTY(QString rawHeader READ rawHeader)
    Q_PROPERTY(QString requestBody READ requestBody)
public:
    explicit WebAppRequest(QObject *parent = 0);
    ~WebAppRequest();

    enum RequestType {
        GET,
        PUT,
        POST
    };

    RequestType requestType() const;
    QString unhandledUri() const;
    QUrl url() const;
    QStringList resources() const;
    QString currentResourceName() const;
    int currentResourceIndex() const;
    QTcpSocket *socket() const;
    WebAppResponse *response() const;
    QMap<QString, QString> headers() const;
    QString rawHeader() const;
    QString requestBody() const;

signals:
    void requestTypeChanged(RequestType type);
    void unhandledUriChanged(QString uri);
    void urlChanged(QUrl url);
    void resourcesChanged(QStringList resources);
    void currentResourceNameChanged(QString currentResourceName);
    void currentResourceIndexChanged(int index);
    void socketChanged(QTcpSocket *socket);
    void responseChanged(WebAppResponse *response);

    void requestDataReady(WebAppRequest *request);
public slots:
    void setRequestType(RequestType type);
    void setUnhandledUri(QString uri);
    void setUrl(QUrl url);
    void setResources(QStringList resources);
    void setCurrentResourceName(QString currentResourceName);
    void setCurrentResourceIndex(int index);
    void setSocket(QTcpSocket *socket);
    void setResponse(WebAppResponse *response);

private slots:
    void requestDataReady(QTcpSocket *socket);

private:
    QScopedPointer<WebAppRequestPrivate> p;
};

Q_DECLARE_METATYPE(WebAppRequest *)

#endif // WEBAPPREQUEST_H
