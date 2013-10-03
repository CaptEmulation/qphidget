import QtQuick 2.0

Rectangle {
    id: output
    width: 36
    height: 36

    state: "OFF"

    states: [
        State {
            name: "OFF"
            PropertyChanges {
                target: label
                text: qsTr("OFF")
            }
            PropertyChanges {
                target: output
                color: "#ffffff"
            }
        },

        State {
            name: "ON"
            PropertyChanges {
                target: label
                text: qsTr("ON")
            }
            PropertyChanges {
                target: output
                color: "#0000FF"
            }
        }
    ]

    Text {
        id: label
        anchors.fill: parent
    }
}
