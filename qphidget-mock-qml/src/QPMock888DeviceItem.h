#ifndef QPMOCK888DEVICEITEM_H
#define QPMOCK888DEVICEITEM_H

#include <QQuickItem>
#include "QPMock888Device.h"
#include "QPMockBehavior.h"


class QPMock888DeviceItemPrivate;

class QPMock888DeviceItem : public QQuickItem
{
    friend class QPMock888DeviceItemPrivate;

    Q_OBJECT
    Q_PROPERTY(qint32 uid READ uid WRITE setUid NOTIFY uidChanged)
    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)
    Q_PROPERTY(bool input0 READ input0 WRITE setInput0 NOTIFY input0Changed)
    Q_PROPERTY(bool input1 READ input1 WRITE setInput1 NOTIFY input1Changed)
    Q_PROPERTY(bool output0 READ output0 NOTIFY output0Changed)
    Q_PROPERTY(bool output1 READ output1 NOTIFY output1Changed)

public:
    explicit QPMock888DeviceItem(QQuickItem *parent = 0);
    ~QPMock888DeviceItem();

    qint32 uid();

    bool connected();
    bool input0();
    bool input1();

    bool output0();
    bool output1();

signals:
    void uidChanged(qint32 uid);

    void connectedChanged(bool connected);
    void input0Changed(bool state);
    void input1Changed(bool state);

    void output0Changed(bool state);
    void output1Changed(bool state);

public slots:
    void setUid(quint32 uid);
    void setInput0(bool state);
    void setInput1(bool state);

    void inputChanged(int index, bool input);
    void outputChanged(int index, bool output);

private:
    QScopedPointer<QPMock888DeviceItemPrivate> p;
};

#endif // QPMOCK888DEVICEITEM_H
