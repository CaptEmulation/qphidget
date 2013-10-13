#ifndef HVACZONE_H
#define HVACZONE_H

#include <QObject>

class HvacZone : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString mode READ mode WRITE setMode NOTIFY modeChanged)
    Q_PROPERTY(QString fanMode READ fanMode WRITE setFanMode NOTIFY fanModeChanged)
    QString m_name;

    QString m_mode;

    QString m_fanMode;

public:
    explicit HvacZone(QObject *parent = 0);

QString name() const
{
    return m_name;
}

QString mode() const
{
    return m_mode;
}

QString fanMode() const
{
    return m_fanMode;
}

signals:

void nameChanged(QString arg);

void modeChanged(QString arg);

void fanModeChanged(QString arg);

public slots:

void setName(QString arg)
{
    if (m_name != arg) {
        m_name = arg;
        emit nameChanged(arg);
    }
}
void setMode(QString arg)
{
    if (m_mode != arg) {
        m_mode = arg;
        emit modeChanged(arg);
    }
}
void setFanMode(QString arg)
{
    if (m_fanMode != arg) {
        m_fanMode = arg;
        emit fanModeChanged(arg);
    }
}
};

#endif // HVACZONE_H
