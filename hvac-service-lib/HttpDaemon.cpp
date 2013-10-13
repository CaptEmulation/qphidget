#include "HttpDaemon.h"

#include <QTcpSocket>
#include <QStringList>
#include <QDateTime>

class HttpDaemonPrivate {
public:

    HttpDaemon *self;
    bool mDisabled;


    void incomingConnection(int socket) {
        if (mDisabled)
            return;

        // When a new client connects, the server constructs a QTcpSocket and all
        // communication with the client is done over this QTcpSocket. QTcpSocket
        // works asynchronously, this means that all the communication is done
        // in the two slots readClient() and discardClient().
        QTcpSocket* s = new QTcpSocket(self);
        QObject::connect(s, SIGNAL(readyRead()), self, SLOT(readClient()));
        QObject::connect(s, SIGNAL(disconnected()), self, SLOT(discardClient()));
        s->setSocketDescriptor(socket);
    }

    void pause() {
        mDisabled = true;
    }

    void resume() {
        mDisabled = false;
    }

    void readClient()
    {
        if (mDisabled)
            return;

        // This slot is called when the client sent data to the server. The
        // server looks if it was a get request and sends a very simple HTML
        // document back.
        QTcpSocket* socket = (QTcpSocket*)self->sender();
        if (socket->canReadLine()) {
            emit self->readData(socket);
        }
    }
    void discardClient()
    {
        QTcpSocket* socket = (QTcpSocket*)self->sender();
        socket->deleteLater();
    }

};


HttpDaemon::HttpDaemon(quint16 port, QObject *parent)
    : QTcpServer(parent),
      p(new HttpDaemonPrivate)
{
    p->self = this;
    p->mDisabled = false;
    listen(QHostAddress::Any, port);
}

HttpDaemon::~HttpDaemon()
{

}

void HttpDaemon::incomingConnection(int socket)
{
    p->incomingConnection(socket);
}

void HttpDaemon::pause()
{
    p->pause();
}

void HttpDaemon::resume()
{
    p->resume();
}

void HttpDaemon::readClient()
{
    p->readClient();
}

void HttpDaemon::discardClient()
{
    p->discardClient();
}
