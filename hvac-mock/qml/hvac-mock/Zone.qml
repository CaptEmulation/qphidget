import QtQuick 2.1
import QtQuick.Controls 1.0

Rectangle {
    id: rectangle1
    x: 0
    width: parent.width
    height: 140
    color: Qt.hsla(hue(), 0.6, 0.7, 1)

    property bool heating
    property bool cooling
    property bool fan

    heating: thermo.heating
    cooling: thermo.cooling
    fan: thermo.fan

    function hue() {
        var modifier = (144 + 5 * thermo.farenheit) / 740;
        return modifier > 0 ? modifier : -modifier;
    }

    Thermostat {
        id: thermo
        state: 'cooling'

        setPoint: 76
        farenheit: 73
    }

    Row {
        width: parent.width
        height: parent.height
        anchors.left: parent.left
        anchors.verticalCenter: parent.Center

        Column {

           width: childrenRect.width
           height:  parent.height

           Text {
               font.pixelSize: 18
               width: parent.width
               horizontalAlignment: Text.AlignHCenter
               text: 'Temperature'
           }

           Row {
               height: parent.height
               width: childrenRect.width

               spacing: 8

               Text {
                   id: temp
                   font.pixelSize: 24
                   anchors.verticalCenter: parent.Center
                   height: parent.height
                   verticalAlignment: Text.AlignVCenter
                   text: thermo.farenheit + " F"
               }

               Rocker {
                   anchors.verticalCenter: parent.Center
                   anchors.top: parent.top
                   anchors.topMargin: 24
                   anchors.bottom: parent.bottom
                   anchors.bottomMargin: 24
                   onIncrement: thermo.farenheit++
                   onDecrement: thermo.farenheit--
               }
           }

        }

        Column {

           width: childrenRect.width
           height:  parent.height

           Text {
               font.pixelSize: 18
               width: parent.width
               horizontalAlignment: Text.AlignHCenter
               text: 'Set Point'
           }

           Row {
               height: parent.height
               width: childrenRect.width

               spacing: 8

               Text {
                    id: setPoint
                    font.pixelSize: 24
                    anchors.verticalCenter: parent.Center
                    height: parent.height
                    verticalAlignment: Text.AlignVCenter

                    text: thermo.setPoint + " F"
                }

                Rocker {
                    anchors.verticalCenter: parent.Center
                    anchors.top: parent.top
                    anchors.topMargin: 24
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 24
                    onIncrement: thermo.setPoint++
                    onDecrement: thermo.setPoint--
                }
           }
        }

        GroupBox {
            title: qsTr("Mode")

            Column {
                ExclusiveGroup { id: mode }
                RadioButton {
                    id: heatMode
                    text: qsTr("Heat")
                    exclusiveGroup: mode
                    onClicked: thermo.state = "heating"
                }
                RadioButton {
                    id: coolMode
                    text: qsTr("Cool")
                    exclusiveGroup: mode
                    checked: true
                    onClicked: thermo.state = "cooling"
                }
                RadioButton {
                    id: offMode
                    text: qsTr("Off")
                    exclusiveGroup: mode
                    onClicked: thermo.state = "off"
                }
            }
        }

        GroupBox {
            title: qsTr("Fan")
            Column {
                ExclusiveGroup { id: fanMode }
                RadioButton {
                    id: fanAutoMode
                    text: qsTr("Auto")
                    exclusiveGroup: fanMode
                    checked: true
                    onClicked: thermo.fanMotor.state = "auto"
                }
                RadioButton {
                    id: fanOnMode
                    text: qsTr("On")
                    exclusiveGroup: fanMode
                    onClicked: thermo.fanMotor.state = "on"
                }
            }
        }
    }

}
