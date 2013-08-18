import QtQuick 2.0
import com.soapbubble.qphidget 1.0

Rectangle {
    width: 360
    height: 360
    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            ifk.output0 = !ifk.output0;
        }
    }


    IFK888 {
        id: ifk
        onInput0Changed: {
            console.log('Input0: ' + state)
        }
    }
}
