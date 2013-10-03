import QtQuick 2.0
import com.captemulation.qphidget.mock 1.0

Rectangle {
    id: root
    width: 320
    height: 240


    Mock888Device {
        id: mock888

        function boolToState(digital) {
            if (digital) {
                return "ON"
            }
            return "OFF"
        }

        onOutput0Changed: output0.state = boolToState(mock888.output0)
        onInput0Changed: input0.state = boolToState(mock888.input0)
    }

    DigitalOutput {
        id: output0
        anchors.top: root.top
        anchors.topMargin: 8
        anchors.left: root.left
        anchors.leftMargin: 8

    }

    DigitalInput {
        id: input0
        anchors.top: root.top
        anchors.topMargin: 8
        anchors.right: root.right
        anchors.rightMargin: 8

        MouseArea {
            anchors.fill: parent
            onClicked: {
                mock888.input0 = !mock888.input0;
            }
        }
    }

}
