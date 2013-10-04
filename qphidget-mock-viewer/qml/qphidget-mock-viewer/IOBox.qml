import QtQuick 2.0

Rectangle {
    id: output

    property string offColor: 'white'
    property string onColor: 'red'
    property string borderColor: 'black'

    width: 36
    height: 36
    border.color: borderColor

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
                color: offColor
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
                color: onColor
            }
        }
    ]

    Text {
        id: label
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
