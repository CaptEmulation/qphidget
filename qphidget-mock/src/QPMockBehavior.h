#ifndef QPMOCKBEHAVIOR_H
#define QPMOCKBEHAVIOR_H

#include "QPMockUpdateDelegate.h"

#include <QObject>
#include <QTime>

class QPMockBehaviorPrivate;

class QPMockBehavior : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QTime currentTime READ currentTime WRITE setCurrentTime NOTIFY currentTimeChanged)
    Q_PROPERTY(qint32 tickMs READ tickMs WRITE setTickMs NOTIFY tickMsChanged)
    Q_PROPERTY(QList<QPMockUpdateDelegate *> behaviors READ behaviors)

public:
    QPMockBehavior(QObject *parent = 0);
    ~QPMockBehavior();

    void tick();

    QTime currentTime() const;
    qint32 tickMs();
    QList<QPMockUpdateDelegate *> behaviors();
    void addBehavior(QPMockUpdateDelegate *behavior);
public slots:
    void setCurrentTime(QTime time);
    void setTickMs(qint32 mseconds);
signals:
    void currentTimeChanged(QTime time);
    void tickMsChanged(qint32 mseconds);
protected:

private:
    QScopedPointer<QPMockBehaviorPrivate> p;
};

Q_DECLARE_METATYPE(QPMockBehavior *)

#endif // QPMOCKBEHAVIOR_H
