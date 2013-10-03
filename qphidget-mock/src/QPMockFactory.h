#ifndef QPMOCKFACTORY_H
#define QPMOCKFACTORY_H

#include <QObject>
#include "QPMock888Device.h"

class QPMockFactoryPrivate;

class QPMockFactory : public QObject
{
    Q_OBJECT
public:
    explicit QPMockFactory(QObject *parent = 0);
    ~QPMockFactory();

    Q_INVOKABLE void create();

    QPMock888Device *ifk888(qint32 id = -1);


private:

    QScopedPointer<QPMockFactoryPrivate> p;
};

#endif // QPMOCKFACTORY_H
