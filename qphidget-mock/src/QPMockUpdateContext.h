#ifndef QPMOCKBEHAVIORCONTEXT_H
#define QPMOCKBEHAVIORCONTEXT_H

#include <QObject>
#include <QTime>

class QPMockUpdateContextPrivate;

class QPMockUpdateContext : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QTime currentTime READ currentTime WRITE setCurrentTime NOTIFY currentTimeChanged)

public:
    explicit QPMockUpdateContext(QObject *parent = 0);
    ~QPMockUpdateContext();

    QTime currentTime() const;

signals:
    void currentTimeChanged(QTime time);

public slots:
    void setCurrentTime(QTime time);

private:
    QScopedPointer<QPMockUpdateContextPrivate> p;

};

Q_DECLARE_METATYPE(QPMockUpdateContext *)

#endif // QPMOCKBEHAVIORCONTEXT_H
