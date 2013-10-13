#ifndef WEBAPPRESPONSE_H
#define WEBAPPRESPONSE_H

#include <QObject>

class WebAppResponse : public QObject
{
    Q_OBJECT
public:
    explicit WebAppResponse(QObject *parent = 0);

signals:

public slots:

};

Q_DECLARE_METATYPE(WebAppResponse *)

#endif // WEBAPPRESPONSE_H
