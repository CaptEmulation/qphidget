#ifndef QPMOCKDATABEHAVIOR_H
#define QPMOCKDATABEHAVIOR_H

#include "QPMockBehaviorDelegate.h"
#include <QDataStream>

class QPMockDataBehaviorPrivate;

class QPMockDataBehavior : public QPMockBehaviorDelegate
{
    Q_OBJECT
    Q_PROPERTY(QDataStream data READ data)
public:
    explicit QPMockDataBehavior(QObject *parent = 0);
    ~QPMockDataBehavior();

    QDataStream data();
signals:

public slots:

protected:
    void doUpdate(QPMockBehaviorContext *context);

private:
    QScopedPointer<QPMockDataBehaviorPrivate> p;
};

#endif // QPMOCKDATABEHAVIOR_H
