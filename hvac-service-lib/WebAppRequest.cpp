#include "WebAppRequest.h"


class WebAppRequestPrivate {
public:
    WebAppRequest *self;
    WebAppRequest::RequestType mType;
    QString mRemainingUri;
    QUrl mUrl;
    QStringList mResources;
    QString mCurrentResourceName;
    int mCurrentResourceIndex;
    QTcpSocket *mSocket;
    WebAppResponse *mResponse;
    QMap<QString, QString> mHeaders;
    QString mRequestHeader;
    QString mRequestBody;

    QString unhandledUri() const {
        return mRemainingUri;
    }

    void setUnhandledUri(QString uri) {
        if (uri != mRemainingUri) {
            mRemainingUri = uri;
            emit self->unhandledUriChanged(uri);
        }
    }

    QUrl url() const {
        return mUrl;
    }

    void setUrl(QUrl url) {
        if (mUrl != url) {
            mUrl = url;
            emit self->urlChanged(url);
        }
    }

    QStringList resources() const {
        return mResources;
    }

    void setResources(QStringList resources) {
        if (mResources != resources) {
            mResources = resources;
            emit self->resourcesChanged(resources);
        }
    }

    QTcpSocket *socket() {
        return mSocket;
    }

    void setSocket(QTcpSocket *socket) {
        if (mSocket != socket) {
            mSocket = socket;
            emit self->socketChanged(socket);
        }
    }

    QString currentResourceName() const {
        return mCurrentResourceName;
    }

    void setCurrentResourceName(QString currentResourceName) {
        if (mCurrentResourceName != currentResourceName) {
            mCurrentResourceName = currentResourceName;
            emit self->currentResourceNameChanged(currentResourceName);
        }
    }
    int currentResourceIndex() const {
        return mCurrentResourceIndex;
    }

    void setCurrentResourceIndex(int index) {
        if (mCurrentResourceIndex != index) {
            mCurrentResourceIndex = index;
            emit self->currentResourceIndexChanged(index);
        }
    }

    WebAppRequest::RequestType requestType() const {
        return mType;
    }

    void setRequestType(WebAppRequest::RequestType type) {
        if (mType != type) {
            mType = type;
            emit self->requestTypeChanged(type);
        }
    }

    WebAppResponse *response() const {
        return mResponse;
    }

    void setResponse(WebAppResponse *response) {
        if (mResponse != response) {
            mResponse = response;
            emit self->responseChanged(response);
        }
    }

    QMap<QString, QString> headers() const {
        return mHeaders;
    }

    QString rawHeader() const {
        return mRequestHeader;
    }

    QString requestBody() const {
        return mRequestBody;
    }

};

WebAppRequest::WebAppRequest(QObject *parent) :
    QObject(parent),
    p(new WebAppRequestPrivate)
{
    p->self = this;
    p->mCurrentResourceIndex = 0;
    p->mResponse = Q_NULLPTR;
    p->mSocket = Q_NULLPTR;
}

WebAppRequest::~WebAppRequest()
{

}

WebAppRequest::RequestType WebAppRequest::requestType() const
{
    return p->requestType();
}

QString WebAppRequest::unhandledUri() const
{
    return p->unhandledUri();
}

QUrl WebAppRequest::url() const
{
    return p->url();
}

QStringList WebAppRequest::resources() const
{
    return p->resources();
}

QTcpSocket *WebAppRequest::socket() const
{
    return p->socket();
}

WebAppResponse *WebAppRequest::response() const
{
    return p->mResponse;
}

QMap<QString, QString> WebAppRequest::headers() const
{
    return p->headers();
}

QString WebAppRequest::rawHeader() const
{
    return p->rawHeader();
}

QString WebAppRequest::requestBody() const
{
    return p->requestBody();
}

QString WebAppRequest::currentResourceName() const
{
    return p->currentResourceName();
}

int WebAppRequest::currentResourceIndex() const
{
    return p->currentResourceIndex();
}

void WebAppRequest::setRequestType(WebAppRequest::RequestType type)
{
    p->setRequestType(type);
}

void WebAppRequest::setUnhandledUri(QString uri)
{
    p->setUnhandledUri(uri);
}

void WebAppRequest::setUrl(QUrl url)
{
    p->setUrl(url);
}

void WebAppRequest::setResources(QStringList resources)
{
    p->setResources(resources);
}

void WebAppRequest::setCurrentResourceName(QString currentResourceName)
{
    p->setCurrentResourceName(currentResourceName);
}

void WebAppRequest::setCurrentResourceIndex(int index)
{
    p->setCurrentResourceIndex(index);
}

void WebAppRequest::setSocket(QTcpSocket *socket)
{
    p->setSocket(socket);
}

void WebAppRequest::setResponse(WebAppResponse *response)
{
    p->setResponse(response);
}

void WebAppRequest::requestDataReady(QTcpSocket *socket)
{
    emit requestDataReady(this);
}
