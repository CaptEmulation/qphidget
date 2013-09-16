#ifndef QPTESTBEHAVIOR_H
#define QPTESTBEHAVIOR_H

#include "QPMockUpdateDelegate.h"

class QPTestBehaviorPrivate;

class QPTestBehavior : public QPMockUpdateDelegate
{
    Q_OBJECT
    Q_PROPERTY(bool wasUpdated READ wasUpdated NOTIFY wasUpdatedChanged)
    Q_PROPERTY(QList<QPMockUpdateContext *> contexts READ contexts NOTIFY contextsChanged)
    //Q_PROPERTY(QPMockUpdateDelegate *decorated READ decorated WRITE setDecorated NOTIFY decoratedChanged)
public:
    explicit QPTestBehavior(QObject *parent = 0);
    ~QPTestBehavior();

    bool wasUpdated();
    QList<QPMockUpdateContext *> contexts();
    //QPMockUpdateDelegate *decorated();
signals:

    void wasUpdatedChanged();
    void contextsChanged(QList<QPMockUpdateContext *> contexts);
    //void decoratedChanged(QPMockUpdateDelegate *decorated);
public slots:

protected:
    void doUpdate(QPMockUpdateContext *context);

private:
    QScopedPointer<QPTestBehaviorPrivate> p;

};

#endif // QPTESTBEHAVIOR_H
