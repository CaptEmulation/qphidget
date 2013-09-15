#ifndef QPTESTBEHAVIOR_H
#define QPTESTBEHAVIOR_H

#include "QPMockBehaviorDelegate.h"

class QPTestBehaviorPrivate;

class QPTestBehavior : public QPMockBehaviorDelegate
{
    Q_OBJECT
    Q_PROPERTY(bool wasUpdated READ wasUpdated NOTIFY wasUpdatedChanged)
    Q_PROPERTY(QList<QPMockBehaviorContext *> contexts READ contexts NOTIFY contextsChanged)
    Q_PROPERTY(QPMockBehaviorDelegate *decorated READ decorated WRITE setDecorated NOTIFY decoratedChanged)
public:
    explicit QPTestBehavior(QObject *parent = 0);
    ~QPTestBehavior();

    bool wasUpdated();
    QList<QPMockBehaviorContext *> contexts();
    QPMockBehaviorDelegate *decorated();
signals:

    void wasUpdatedChanged();
    void contextsChanged(QList<QPMockBehaviorContext *> contexts);
    void decoratedChanged(QPMockBehaviorDelegate *decorated);
public slots:

protected:
    void doUpdate(QPMockBehaviorContext *context);

private:
    QScopedPointer<QPTestBehaviorPrivate> p;

};

#endif // QPTESTBEHAVIOR_H
