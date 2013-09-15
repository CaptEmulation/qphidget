#ifndef QPMOCKBEHAVIORCONTEXT_H
#define QPMOCKBEHAVIORCONTEXT_H

#include <QObject>
#include <QTime>

class QPMockBehaviorContextPrivate;

class QPMockBehaviorContext : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QTime currentTime READ currentTime WRITE setCurrentTime NOTIFY currentTimeChanged)

public:
    explicit QPMockBehaviorContext(QObject *parent = 0);
    ~QPMockBehaviorContext();

    QTime currentTime() const;

signals:
    void currentTimeChanged(QTime time);

public slots:
    void setCurrentTime(QTime time);

private:
    QScopedPointer<QPMockBehaviorContextPrivate> p;

};

Q_DECLARE_METATYPE(QPMockBehaviorContext *)

#endif // QPMOCKBEHAVIORCONTEXT_H
