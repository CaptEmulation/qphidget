import QtQuick 2.1
import QtQuick.Controls 1.0

Rectangle {
    width: 64
    height: 128

    property string topLabel: "Up"
    property string bottomLabel: "Down"
    signal increment
    signal decrement

    Button {
        id: top
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: parent.left
        height: parent.height / 2

        text: topLabel
        onClicked: increment()
    }

    Button {
        id: bottom
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        height: parent.height / 2

        text: bottomLabel
        onClicked: decrement()
    }


}
