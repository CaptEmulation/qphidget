#ifndef HTTPSERVICE_H
#define HTTPSERVICE_H

#include <QScopedPointer>
#include <QTcpServer>

class HttpDaemonPrivate;

// HttpDaemon is the the class that implements the simple HTTP server.
class HttpDaemon : public QTcpServer
{
    friend class HttpDaemonPrivate;
    Q_OBJECT
public:
    HttpDaemon(quint16 port, QObject* parent = 0);

    ~HttpDaemon();

    void incomingConnection(int socket);

    void pause();

    void resume();

signals:
    void readData(QTcpSocket *socket);
    void clientFinished();

private slots:
    void readClient();

    void discardClient();

private:
    QScopedPointer<HttpDaemonPrivate> p;
};

#endif // HTTPSERVICE_H
