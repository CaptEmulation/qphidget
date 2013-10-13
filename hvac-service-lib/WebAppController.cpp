#include "WebAppController.h"
#include <QMap>
#include <QUrl>
#include <QMetaEnum>
#include "HttpDaemon.h"

class WebAppControllerPrivate {
public:
    WebAppController *self;
    HttpDaemon *mDaemon;
    QMap<QTcpSocket *, WebAppRequest *> mRequests;
    QMap<QString, WebAppUriHandler *> mHandlers;
    QMetaEnum mMetaRequest;

    void acceptData(QTcpSocket *socket) {
        if (mRequests.contains(socket)) {
            emit self->requestDataReady(mRequests[socket]);
        } else if (socket->canReadLine()) {
            QObject::connect(socket, SIGNAL(aboutToClose()), self, SLOT(clientFinished()));

            QStringList tokens = QString(socket->readLine()).split(QRegExp("[ \r\n][ \r\n]*"));
            bool validType;
            int index = mMetaRequest.keyToValue(tokens[0].toUtf8().constData(), &validType);
            if (validType) {
                WebAppRequest::RequestType requestType = (WebAppRequest::RequestType)index;
                WebAppRequest *request = new WebAppRequest(self);
                request->setRequestType(requestType);
                request->setSocket(socket);
                request->setUnhandledUri(tokens[1]);
                mRequests.insert(socket, request);
                handleRequest(request);
            } else {
                // TODO: send HTML error
                socket->close();
            }

//            if (tokens[0] == "GET") {
//                QTextStream os(socket);
//                os.setAutoDetectUnicode(true);
//                os << "HTTP/1.0 200 Ok\r\n"
//                    "Content-Type: text/html; charset=\"utf-8\"\r\n"
//                    "\r\n"
//                    "<h1>Nothing to see here</h1>\n"
//                    << QDateTime::currentDateTime().toString() << "\n";
//                socket->close();

//                QtServiceBase::instance()->logMessage("Wrote to client");

            if (socket->state() == QTcpSocket::UnconnectedState) {
                delete socket;
            }
        }
    }

    void addHandler(WebAppUriHandler *handler, QString resource) {
        mHandlers.insert(resource, handler);
    }

    QStringList createResourceList(WebAppRequest *request) {
        return request->unhandledUri().split('/', QString::SkipEmptyParts);
    }

    WebAppResponse *handleRequest(WebAppRequest *request) {
        WebAppResponse *response = new WebAppResponse();
        request->setParent(response);
        request->setResponse(response);
        request->setResources(createResourceList(request));
        request->setCurrentResourceIndex(0);
        request->setCurrentResourceName(request->resources()[0]);
        if (mHandlers.contains(request->currentResourceName())) {
            mHandlers[request->currentResourceName()]->handleRequest(request);
        } else {
            request->socket()->close();
        }
        return response;
    }

    void clientFinished() {
        QTcpSocket *socket = (QTcpSocket*)self->sender();
        if (mRequests.contains(socket)) {
            emit self->responseReady(mRequests[socket]->response());
            mRequests.remove(socket);
        }

    }
};

WebAppController::WebAppController(qint16 port, QObject *parent) :
    QObject(parent),
    p(new WebAppControllerPrivate)
{
    p->self = this;
    p->mDaemon = new HttpDaemon(port, this);
    connect(p->mDaemon, SIGNAL(clientFinished()), this, SLOT(clientFinished()));
    connect(p->mDaemon, SIGNAL(readData(QTcpSocket*)), this, SLOT(acceptData(QTcpSocket*)));

    const QMetaObject &mo = WebAppRequest::staticMetaObject;
    p->mMetaRequest = mo.enumerator(mo.indexOfEnumerator("RequestType"));
}

WebAppController::~WebAppController()
{

}

void WebAppController::addHandler(WebAppUriHandler *handler, QString resource)
{
    p->addHandler(handler, resource);
}

WebAppResponse *WebAppController::handleRequest(WebAppRequest *request)
{
    return p->handleRequest(request);
}

void WebAppController::acceptData(QTcpSocket *socket)
{
    p->acceptData(socket);
}

void WebAppController::clientFinished()
{
    p->clientFinished();
}
