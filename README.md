# QPhidget


## Qt Phidget API
Implementation of the Phidget API exposed as QtObjects

* Event driven
* Translate Phidget events to Qt Signal and Slots mechanism
* QML compatible property bindings
* Unit tests including a mock implemenation of the Phidget21 API

## Usage

### From C++
```
// Create the phidget object
QP888Device *interfaceKit = new QP888Device();
// Connect to one or more signal
QObject::connect(interfaceKit->inputs().at(0), SIGNAL(stateChanged(bool)), this, SLOT(onInput0StateChanged(bool)));
// After opening and once the phidget is connected, signals will begin firing on changes
interfaceKit->open();
```

### From QML
```
Rectangle {
  width: 360
  height: 360
  MouseArea {
      anchors.fill: parent
      onClicked: {
          ifk.output0 = !ifk.output0;
      }
  }
}

IFK888 { // QML Item for InterfaceKit 8/8/8
    id: ifk
    onInput0Changed: {
        console.log('Input0: ' + state)
    }
}
```

## Building
Build has only been tested on Win32 but should be able to compile cross-platform with some additional tweaks to pro files

Requires phidget21 library installed.  See http://www.phidgets.com/docs/Programming_Resources for links to download the library.

Build qphidget-lib, then qphidget-qml then qphidget (the root example app)
