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

#ifndef PHIDGETSERVICE_H
#define PHIDGETSERVICE_H

#include <QObject>
#include "phidget21.h"

class QPManagerDelegate
{
public:
    ~QPManagerDelegate() {}

    virtual void deviceAttached(CPhidgetHandle phidget) = 0;
    virtual void deviceDetached(CPhidgetHandle phidget) = 0;
};

Q_DECLARE_INTERFACE(
        QPManagerDelegate,
        "com.qphidget.QPManagerDelegate/1.0")

class QPManagerPrivate;

class QPManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool ready READ ready NOTIFY readyChanged)
public:
    explicit QPManager(QObject *parent = 0);
    ~QPManager();

    void open();
    void addDeviceInterface(CPhidget_DeviceClass deviceClass, QPManagerDelegate *delegate);

    bool ready();
signals:
    void readyChanged();
    void deviceAttached(CPhidgetHandle phidget);

public slots:
    
private:
    QScopedPointer<QPManagerPrivate> p;
};

#endif // PHIDGETSERVICE_H
