#ifndef QPMockUpdateDelegate_H
#define QPMockUpdateDelegate_H

#include "QPMockUpdateContext.h"

#include <QObject>
#include <QTime>

class QPMockUpdateDelegatePrivate;

class QPMockUpdateDelegate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QTime nextTimeChange READ nextTimeChange WRITE setNextTimeChange NOTIFY nextTimeChangeChanged)


public:
    QPMockUpdateDelegate(QObject *parent = 0);
    ~QPMockUpdateDelegate();

    QTime nextTimeChange() const;

public slots:
    void update(QPMockUpdateContext *context);

    void setNextTimeChange(QTime time);

signals:
    void nextTimeChangeChanged(QTime time);

protected:
    virtual void doUpdate(QPMockUpdateContext *context) = 0;

private:
    QScopedPointer<QPMockUpdateDelegatePrivate> p;
};

Q_DECLARE_METATYPE(QPMockUpdateDelegate *)

#endif // QPMockBehaviorDelegateDELEGATE_H
