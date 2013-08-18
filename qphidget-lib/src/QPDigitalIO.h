/**
Copyright 2013 John Dean, III

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/


#ifndef QPDIGITALINPUT_H
#define QPDIGITALINPUT_H

#include <QObject>
#include "phidget21.h"

class QPDigitalIOPrivate;

class QPDigitalIO : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(CPhidgetInterfaceKitHandle ifk READ ifk WRITE setIfk NOTIFY ifkChanged)

public:
    enum Type {
        Input,
        Output
    };

    explicit QPDigitalIO(Type type, qint32 index, QObject *parent = 0);
    ~QPDigitalIO();

    bool state();
    CPhidgetInterfaceKitHandle ifk();
signals:

    void stateChanged(bool state);
    void ifkChanged(CPhidgetInterfaceKitHandle ifk);

public slots:

    void setState(bool state);
    void setIfk(CPhidgetInterfaceKitHandle ifk);

private:
    QScopedPointer<QPDigitalIOPrivate> p;
};

Q_DECLARE_METATYPE(QPDigitalIO *)

#endif // QPDIGITALINPUT_H
