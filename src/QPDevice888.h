#ifndef QPDEVICE888_H
#define QPDEVICE888_H

#include <QObject>
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


#include "QPDigitalIO.h"
#include "QPManager.h"

class QPDevice888Private;

class QPDevice888 : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ connected WRITE setConnected NOTIFY connectedChanged)
    Q_PROPERTY(QList<QPDigitalIO *> inputs READ inputs)
    Q_PROPERTY(QList<QPDigitalIO *> outputs READ outputs)
    Q_PROPERTY(CPhidgetHandle phidget READ phidget WRITE setPhidget NOTIFY phidgetChanged)


public:
    explicit QPDevice888(QObject *parent = 0);
    ~QPDevice888();

    void open();
    void close();

    bool getInput(qint32 index);
    void setOutput(qint32 index, bool value);

    bool connected();
    QList<QPDigitalIO *> inputs();
    QList<QPDigitalIO *> outputs();
    CPhidgetHandle phidget();

    static CPhidget_DeviceClass deviceClass() {
        return PHIDCLASS_INTERFACEKIT;
    }

signals:
    void connectedChanged();
    void phidgetChanged();

public slots:
    void setConnected(bool connected);
    void setPhidget(CPhidgetHandle phidget);

private:
    QScopedPointer<QPDevice888Private> p;
};

Q_DECLARE_METATYPE(QPDevice888 *)

#endif // QPDEVICE888_H
