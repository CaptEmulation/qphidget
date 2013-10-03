#ifndef QP888DEVICEITEM_H
#define QP888DEVICEITEM_H

#include <QQuickItem>

class QP888DeviceItemPrivate;

class QP888DeviceItem : public QQuickItem
{
    friend class QP888DeviceItemPrivate;

    Q_OBJECT
    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)
    Q_PROPERTY(bool input0 READ input0 WRITE setInput0 NOTIFY input0Changed)
    Q_PROPERTY(bool input1 READ input1 WRITE setInput1 NOTIFY input1Changed)
    Q_PROPERTY(bool output0 READ output0 WRITE setOutput0 NOTIFY output0Changed)

public:
    explicit QP888DeviceItem(QQuickItem *parent = 0);
    ~QP888DeviceItem();
    
    bool connected();
    bool input0();
    bool input1();

    bool output0();

signals:
    void connectedChanged(bool connected);
    void input0Changed(bool state);
    void input1Changed(bool state);

    void output0Changed(bool state);

public slots:
    void setInput0(bool state);
    void setInput1(bool state);
    void setOutput0(bool state);

private:
    QScopedPointer<QP888DeviceItemPrivate> p;
};

#endif // QP888DEVICEITEM_H
