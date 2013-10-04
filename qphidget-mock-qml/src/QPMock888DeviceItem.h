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
    Q_PROPERTY(bool input2 READ input2 WRITE setInput2 NOTIFY input2Changed)
    Q_PROPERTY(bool input3 READ input3 WRITE setInput3 NOTIFY input3Changed)
    Q_PROPERTY(bool input4 READ input4 WRITE setInput4 NOTIFY input4Changed)
    Q_PROPERTY(bool input5 READ input5 WRITE setInput5 NOTIFY input5Changed)
    Q_PROPERTY(bool input6 READ input6 WRITE setInput6 NOTIFY input6Changed)
    Q_PROPERTY(bool input7 READ input7 WRITE setInput7 NOTIFY input7Changed)
    Q_PROPERTY(bool output0 READ output0 NOTIFY output0Changed)
    Q_PROPERTY(bool output1 READ output1 NOTIFY output1Changed)
    Q_PROPERTY(bool output2 READ output2 NOTIFY output2Changed)
    Q_PROPERTY(bool output3 READ output3 NOTIFY output3Changed)
    Q_PROPERTY(bool output4 READ output4 NOTIFY output4Changed)
    Q_PROPERTY(bool output5 READ output5 NOTIFY output5Changed)
    Q_PROPERTY(bool output6 READ output6 NOTIFY output6Changed)
    Q_PROPERTY(bool output7 READ output7 NOTIFY output7Changed)

public:
    explicit QPMock888DeviceItem(QQuickItem *parent = 0);
    ~QPMock888DeviceItem();

    qint32 uid();

    bool connected();
    bool input0();
    bool input1();
    bool input2();
    bool input3();
    bool input4();
    bool input5();
    bool input6();
    bool input7();

    bool output0();
    bool output1();
    bool output2();
    bool output3();
    bool output4();
    bool output5();
    bool output6();
    bool output7();

signals:
    void uidChanged(qint32 uid);

    void connectedChanged(bool connected);
    void input0Changed(bool state);
    void input1Changed(bool state);
    void input2Changed(bool state);
    void input3Changed(bool state);
    void input4Changed(bool state);
    void input5Changed(bool state);
    void input6Changed(bool state);
    void input7Changed(bool state);

    void output0Changed(bool state);
    void output1Changed(bool state);
    void output2Changed(bool state);
    void output3Changed(bool state);
    void output4Changed(bool state);
    void output5Changed(bool state);
    void output6Changed(bool state);
    void output7Changed(bool state);

public slots:
    void setUid(quint32 uid);
    void setInput0(bool state);
    void setInput1(bool state);
    void setInput2(bool state);
    void setInput3(bool state);
    void setInput4(bool state);
    void setInput5(bool state);
    void setInput6(bool state);
    void setInput7(bool state);

    void inputChanged(int index, bool input);
    void outputChanged(int index, bool output);

private:
    QScopedPointer<QPMock888DeviceItemPrivate> p;
};

#endif // QPMOCK888DEVICEITEM_H
