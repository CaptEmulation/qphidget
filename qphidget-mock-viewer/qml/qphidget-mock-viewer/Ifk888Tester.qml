import QtQuick 2.0
import com.captemulation.qphidget 1.0

Rectangle {
    id: root
    width: 320
    height: 240

    IFK888 {
        id: ifk888

        function boolToState(digital) {
            if (digital) {
                return "ON"
            }
            return "OFF"
        }

        onOutput0Changed: do0.state = boolToState(output0)
        onOutput1Changed: do1.state = boolToState(output1)
        onOutput2Changed: do2.state = boolToState(output2)
        onOutput3Changed: do3.state = boolToState(output3)
        onOutput4Changed: do4.state = boolToState(output4)
        onOutput5Changed: do5.state = boolToState(output5)
        onOutput6Changed: do6.state = boolToState(output6)
        onOutput7Changed: do7.state = boolToState(output7)
        onInput0Changed: di0.state = boolToState(input0)
        onInput1Changed: di1.state = boolToState(input1)
        onInput2Changed: di2.state = boolToState(input2)
        onInput3Changed: di3.state = boolToState(input3)
        onInput4Changed: di4.state = boolToState(input4)
        onInput5Changed: di5.state = boolToState(input5)
        onInput6Changed: di6.state = boolToState(input6)
        onInput7Changed: di7.state = boolToState(input7)
    }
    Text {
        id: digitalOutputLabel
        x: 0
        y: 8
        width: parent.width / 2
        text: qsTr("Digital Outputs")
        horizontalAlignment: Text.AlignHCenter
        anchors.left: parent.left
        anchors.leftMargin: 0
        font.pixelSize: 12
    }

    Text {
        id: digitalInputLabel
        x: 0
        y: 8
        width: parent.width / 2
        text: qsTr("Digital Inputs")
        horizontalAlignment: Text.AlignHCenter
        anchors.right: parent.right
        anchors.rightMargin: 0
        font.pixelSize: 12
    }

    Row {
        id: row1

        property int columnWidth: ((width - (spacing * (children.length - 1))) / children.length)

        anchors.top: digitalOutputLabel.bottom
        anchors.topMargin: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 8
        spacing: 8

        Column {
            id: column1

            property int rowHeight: ((height - (spacing * (children.length - 1))) / children.length)

            width: parent.columnWidth
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            spacing: 8

            Rectangle {
                height: parent.rowHeight
                anchors.left: parent.left
                anchors.right: parent.right

                DigitalOutput {
                    id: do0
                    anchors.left: doLabel0.right
                    anchors.leftMargin: 8
                    anchors.right: parent.right
                    anchors.rightMargin: 8
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            ifk888.output0 = !ifk888.output0
                        }
                    }
                }

                Text {
                    id: doLabel0
                    text: qsTr("0")
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                    anchors.verticalCenter: do0.verticalCenter
                    font.pixelSize: 12
                }
            }


            Rectangle {
                height: parent.rowHeight
                anchors.left: parent.left
                anchors.right: parent.right

                DigitalOutput {
                    id: do1
                    anchors.left: doLabel1.right
                    anchors.leftMargin: 8
                    anchors.right: parent.right
                    anchors.rightMargin: 8
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            ifk888.output1 = !ifk888.output1
                        }
                    }
                }

                Text {
                    id: doLabel1
                    text: qsTr("1")
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                    anchors.verticalCenter: do1.verticalCenter
                    font.pixelSize: 12
                }
            }

            Rectangle {
                height: parent.rowHeight
                anchors.left: parent.left
                anchors.right: parent.right


                DigitalOutput {
                    id: do2
                    anchors.left: doLabel2.right
                    anchors.leftMargin: 8
                    anchors.right: parent.right
                    anchors.rightMargin: 8
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            ifk888.output2 = !ifk888.output2
                        }
                    }
                }

                Text {
                    id: doLabel2
                    text: qsTr("2")
                    font.pixelSize: 12
                    anchors.verticalCenter: do2.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                }
            }

            Rectangle {
                height: parent.rowHeight
                anchors.left: parent.left
                anchors.right: parent.right

                DigitalOutput {
                    id: do3
                    anchors.left: doLabel3.right
                    anchors.leftMargin: 8
                    anchors.right: parent.right
                    anchors.rightMargin: 8
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            ifk888.output3 = !ifk888.output3
                        }
                    }
                }

                Text {
                    id: doLabel3
                    text: qsTr("3")
                    font.pixelSize: 12
                    anchors.verticalCenter: do3.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                }
            }
        }

        Column {
            id: column2

            property int rowHeight: ((height - (spacing * (children.length - 1))) / children.length)

            width: parent.columnWidth
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            spacing: 8

            Rectangle {
                height: parent.rowHeight
                anchors.left: parent.left
                anchors.right: parent.right

                DigitalOutput {
                    id: do4
                    anchors.left: doLabel4.right
                    anchors.leftMargin: 8
                    anchors.right: parent.right
                    anchors.rightMargin: 8
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            ifk888.output4 = !ifk888.output4
                        }
                    }
                }

                Text {
                    id: doLabel4
                    text: qsTr("4")
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                    font.pixelSize: 12
                    anchors.verticalCenter: do4.verticalCenter
                }
            }

            Rectangle {
                height: parent.rowHeight
                anchors.left: parent.left
                anchors.right: parent.right

                DigitalOutput {
                    id: do5
                    anchors.left: doLabel5.right
                    anchors.leftMargin: 8
                    anchors.right: parent.right
                    anchors.rightMargin: 8
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            ifk888.output5 = !ifk888.output5
                        }
                    }
                }

                Text {
                    id: doLabel5
                    text: qsTr("5")
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                    font.pixelSize: 12
                    anchors.verticalCenter: do5.verticalCenter
                }
            }

            Rectangle {
                height: parent.rowHeight
                anchors.left: parent.left
                anchors.right: parent.right

                DigitalOutput {
                    id: do6
                    anchors.left: doLabel6.right
                    anchors.leftMargin: 8
                    anchors.right: parent.right
                    anchors.rightMargin: 8
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            ifk888.output6 = !ifk888.output6
                        }
                    }
                }

                Text {
                    id: doLabel6
                    text: qsTr("6")
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                    font.pixelSize: 12
                    anchors.verticalCenter: do6.verticalCenter
                }
            }
            Rectangle {
                height: parent.rowHeight
                anchors.left: parent.left
                anchors.right: parent.right

                DigitalOutput {
                    id: do7
                    anchors.left: doLabel7.right
                    anchors.leftMargin: 8
                    anchors.right: parent.right
                    anchors.rightMargin: 8
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            ifk888.output7 = !ifk888.output7
                        }
                    }
                }

                Text {
                    id: doLabel7
                    text: qsTr("7")
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                    font.pixelSize: 12
                    anchors.verticalCenter: do7.verticalCenter
                }
            }
        }

        Column {
            id: column3

            property int rowHeight: ((height - (spacing * (children.length - 1))) / children.length)

            width: parent.columnWidth
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            spacing: 8

            Rectangle {
                height: parent.rowHeight
                anchors.left: parent.left
                anchors.right: parent.right

                DigitalInput {
                    id: di0
                    anchors.left: diLabel0.right
                    anchors.leftMargin: 8
                    anchors.right: parent.right
                    anchors.rightMargin: 8
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                }

                Text {
                    id: diLabel0
                    text: qsTr("0")
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                    anchors.verticalCenter: di0.verticalCenter
                    font.pixelSize: 12
                }
            }


            Rectangle {
                height: parent.rowHeight
                anchors.left: parent.left
                anchors.right: parent.right

                DigitalInput {
                    id: di1
                    anchors.left: diLabel1.right
                    anchors.leftMargin: 8
                    anchors.right: parent.right
                    anchors.rightMargin: 8
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                }

                Text {
                    id: diLabel1
                    text: qsTr("1")
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                    anchors.verticalCenter: di1.verticalCenter
                    font.pixelSize: 12
                }
            }

            Rectangle {
                height: parent.rowHeight
                anchors.left: parent.left
                anchors.right: parent.right


                DigitalInput {
                    id: di2
                    anchors.left: diLabel2.right
                    anchors.leftMargin: 8
                    anchors.right: parent.right
                    anchors.rightMargin: 8
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                }

                Text {
                    id: diLabel2
                    text: qsTr("2")
                    font.pixelSize: 12
                    anchors.verticalCenter: di2.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                }
            }

            Rectangle {
                height: parent.rowHeight
                anchors.left: parent.left
                anchors.right: parent.right

                DigitalInput {
                    id: di3
                    anchors.left: diLabel3.right
                    anchors.leftMargin: 8
                    anchors.right: parent.right
                    anchors.rightMargin: 8
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                }

                Text {
                    id: diLabel3
                    text: qsTr("3")
                    font.pixelSize: 12
                    anchors.verticalCenter: di3.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                }
            }
        }

        Column {
            id: column4

            property int rowHeight: ((height - (spacing * (children.length - 1))) / children.length)

            width: parent.columnWidth
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            spacing: 8

            Rectangle {
                height: parent.rowHeight
                anchors.left: parent.left
                anchors.right: parent.right

                DigitalInput {
                    id: di4
                    anchors.left: diLabel4.right
                    anchors.leftMargin: 8
                    anchors.right: parent.right
                    anchors.rightMargin: 8
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                }

                Text {
                    id: diLabel4
                    text: qsTr("4")
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                    anchors.verticalCenter: di4.verticalCenter
                    font.pixelSize: 12
                }
            }


            Rectangle {
                height: parent.rowHeight
                anchors.left: parent.left
                anchors.right: parent.right

                DigitalInput {
                    id: di5
                    anchors.left: diLabel5.right
                    anchors.leftMargin: 8
                    anchors.right: parent.right
                    anchors.rightMargin: 8
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                }

                Text {
                    id: diLabel5
                    text: qsTr("5")
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                    anchors.verticalCenter: di5.verticalCenter
                    font.pixelSize: 12
                }
            }

            Rectangle {
                height: parent.rowHeight
                anchors.left: parent.left
                anchors.right: parent.right


                DigitalInput {
                    id: di6
                    anchors.left: diLabel6.right
                    anchors.leftMargin: 8
                    anchors.right: parent.right
                    anchors.rightMargin: 8
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                }

                Text {
                    id: diLabel6
                    text: qsTr("6")
                    font.pixelSize: 12
                    anchors.verticalCenter: di6.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                }
            }

            Rectangle {
                height: parent.rowHeight
                anchors.left: parent.left
                anchors.right: parent.right

                DigitalInput {
                    id: di7
                    anchors.left: diLabel7.right
                    anchors.leftMargin: 8
                    anchors.right: parent.right
                    anchors.rightMargin: 8
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                }

                Text {
                    id: diLabel7
                    text: qsTr("7")
                    font.pixelSize: 12
                    anchors.verticalCenter: di7.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                }
            }
        }

    }
}
