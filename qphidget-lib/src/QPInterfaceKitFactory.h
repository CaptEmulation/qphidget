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


#ifndef QPINTERFACEKITFACTORY_H
#define QPINTERFACEKITFACTORY_H

#include <QObject>

#include "QPManager.h"
#include "QPDevice888.h"

class QPInterfaceKitFactoryPrivate;

class QPInterfaceKitFactory : public QObject, public QPManagerDelegate
{
    Q_OBJECT
    Q_INTERFACES(QPManagerDelegate)

public:
    explicit QPInterfaceKitFactory(QObject *parent = 0);
    ~QPInterfaceKitFactory();

    static CPhidget_DeviceClass deviceClass() {
        return PHIDCLASS_INTERFACEKIT;
    }

    void deviceAttached(CPhidgetHandle phidget);
    void deviceDetached(CPhidgetHandle phidget);

    Q_INVOKABLE void createDeviceForHandle(CPhidgetHandle phidget);

    QPDevice888 *getDevice();
    
signals:
    
    void deviceAvailable(QPDevice888 *device);
public slots:
    

private:
    QScopedPointer<QPInterfaceKitFactoryPrivate> p;
};

#endif // QPINTERFACEKITFACTORY_H
