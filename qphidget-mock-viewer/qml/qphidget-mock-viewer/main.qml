import QtQuick 2.0
import com.captemulation.qphidget.mock 1.0
import com.captemulation.qphidget 1.0

Rectangle {
    width: 360
    height: 360
    Text {
        id: foo

        text: qsTr("Hello World")
        anchors.centerIn: parent
    }

    Mock888Device {
        id: mock888
    }

    IFK888 {
        id: ifk888

    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            mock888.input0 = !mock888.input0;
            foo.text = "bar"
        }
    }


}
