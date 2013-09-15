#ifndef QPMockBehaviorDelegateDELEGATE_H
#define QPMockBehaviorDELEGATE_H

#include "QPMockBehaviorContext.h"

#include <QObject>
#include <QTime>

class QPMockBehaviorDelegatePrivate;

class QPMockBehaviorDelegate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QTime nextTimeChange READ nextTimeChange WRITE setNextTimeChange NOTIFY nextTimeChangeChanged)


public:
    QPMockBehaviorDelegate(QObject *parent = 0);
    ~QPMockBehaviorDelegate();

    QTime nextTimeChange() const;

public slots:
    void update(QPMockBehaviorContext *context);

    void setNextTimeChange(QTime time);

signals:
    void nextTimeChangeChanged(QTime time);

protected:
    virtual void doUpdate(QPMockBehaviorContext *context) = 0;

private:
    QScopedPointer<QPMockBehaviorDelegatePrivate> p;
};

Q_DECLARE_METATYPE(QPMockBehaviorDelegate *)

#endif // QPMockBehaviorDelegateDELEGATE_H
