#include "WebAppUriHandler.h"

class WebAppUriHandlerPrivate {
public:
    WebAppUriHandler *self;

    void handleRequest(WebAppRequest *request) {

    }
};

WebAppUriHandler::WebAppUriHandler(QObject *parent) :
    QObject(parent),
    p(new WebAppUriHandlerPrivate)
{
    p->self = this;
}

WebAppUriHandler::~WebAppUriHandler()
{
}

void WebAppUriHandler::handleRequest(WebAppRequest *request)
{
    p->handleRequest(request);
}
