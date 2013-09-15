#ifndef QPMOCKBEHAVIOR_H
#define QPMOCKBEHAVIOR_H

#include "QPMockBehaviorContext.h"

#include <QObject>
#include <QTime>

class QPMockBehaviorPrivate;

class QPMockBehavior : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QTime currentTime READ currentTime WRITE setCurrentTime NOTIFY currentTimeChanged)
    Q_PROPERTY(qint32 tickMs READ tick WRITE setTick NOTIFY tickChanged)


public:
    QPMockBehavior(QObject *parent = 0);
    ~QPMockBehavior();

    QTime currentTime() const;
    qint32 tick();
public slots:
    void setCurrentTime(QTime time);
    void setTick(qint32 mseconds);
signals:
    void currentTimeChanged(QTime time);
    void tickChanged(qint32 mseconds);
protected:

private:
    QScopedPointer<QPMockBehaviorPrivate> p;
};

Q_DECLARE_METATYPE(QPMockBehavior *)

#endif // QPMOCKBEHAVIOR_H
