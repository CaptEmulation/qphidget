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


#ifndef QPMOCK_H
#define QPMOCK_H

#include <QObject>
#include "phidget21.h"

class QPMockPrivate;
/**
 * @brief The QPMock class is a phidget library for the tests
 */
class QPMock : public QObject
{
    Q_OBJECT
public:
    explicit QPMock(QObject *parent = 0);
    ~QPMock();

    static QPMock *singleton;

    bool isConnected();
    void setConnected(bool connected);

    int appendAttachListener(CPhidgetManagerHandle phidm, int (*fptr)(CPhidgetHandle, void *), void *userPtr);
    void attached(CPhidgetHandle device);
    int appendDetachListener(CPhidgetManagerHandle phidm, int (*fptr)(CPhidgetHandle, void *), void *userPtr);
    int appendErrorListener(CPhidgetManagerHandle phidm, int (*fptr)(CPhidgetManagerHandle, void *, int, const char *), void *userPtr);
    int getAttachedDevices(CPhidgetManagerHandle phidm, CPhidgetHandle *phidArray[], int *count);

    QList<CPhidgetHandle> mocks();
    void appendMock(CPhidgetHandle device);
    CPhidgetHandle getMockOfClass(CPhidget_DeviceClass deviceClass);

    QPMockDevice *mockInterfaceKey();

signals:

public slots:

private:
    QScopedPointer<QPMockPrivate> p;
};

#endif // QPMOCK_H
