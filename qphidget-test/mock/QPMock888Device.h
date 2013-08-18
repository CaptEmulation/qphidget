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


#ifndef QPMOCK888DEVICE_H
#define QPMOCK888DEVICE_H

#include <QObject>
#include <mock/QPMockDevice.h>

class QPMock888DevicePrivate;

class QPMock888Device : public QPMockDevice
{
    Q_OBJECT
public:
    explicit QPMock888Device(QObject *parent = 0);
    
    int setOnInputChange(int (*fptr)(CPhidgetInterfaceKitHandle, void *, int, int), void *userPtr);
    int setInput(int index, bool input);

signals:
    
public slots:
    
private:
    QScopedPointer<QPMock888DevicePrivate> p;
};

#endif // QPMOCK888DEVICE_H
