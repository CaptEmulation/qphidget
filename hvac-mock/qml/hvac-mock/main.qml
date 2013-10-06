import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.1
import "../../../qml"

ApplicationWindow {
    title: qsTr("HVAC Phidget Simulator")
    width: 800
    height: 400

    Component.onCompleted: show()
    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                shortcut: 'q'
                onTriggered: Qt.quit();
            }
        }
    }

    Row {
        anchors.margins: 12
        anchors.fill: parent
        spacing: 12

        MockIFK888 {
        }

        HouseHvac {
        }
    }



}
