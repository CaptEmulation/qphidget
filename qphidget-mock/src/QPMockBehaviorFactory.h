#ifndef QPMOCKBEHAVIORFACTORY_H
#define QPMOCKBEHAVIORFACTORY_H

#include <QObject>

#include "QPMockBehavior.h"
#include "QPMockDevice.h"

class QPMockBehaviorFactoryPrivate;

class QPMockBehaviorFactory : public QObject
{
    Q_OBJECT
public:
    explicit QPMockBehaviorFactory(QObject *parent = 0);

    QPMockBehavior *createBehavior(QPMockDevice *device, QVariantList behaviors);

signals:

public slots:

};

#endif // QPMOCKBEHAVIORFACTORY_H
