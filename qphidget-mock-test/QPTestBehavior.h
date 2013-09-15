#ifndef QPTESTBEHAVIOR_H
#define QPTESTBEHAVIOR_H

#include "QPMockBehaviorDelegate.h"

class QPTestBehaviorPrivate;

class QPTestBehavior : public QPMockBehaviorDelegate
{
    Q_OBJECT
    Q_PROPERTY(bool wasUpdated READ wasUpdated NOTIFY wasUpdatedChanged)
    Q_PROPERTY(QList<QPMockBehaviorContext *> contexts READ contexts NOTIFY contextsChanged)
public:
    explicit QPTestBehavior(QObject *parent = 0);
    ~QPTestBehavior();

    bool wasUpdated();
    QList<QPMockBehaviorContext *> contexts();
signals:

    void wasUpdatedChanged();
    void contextsChanged(QList<QPMockBehaviorContext *> contexts);
public slots:

protected:
    void doUpdate(QPMockBehaviorContext *context);

private:
    QScopedPointer<QPTestBehaviorPrivate> p;

};

#endif // QPTESTBEHAVIOR_H
