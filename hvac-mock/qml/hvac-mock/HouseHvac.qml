import QtQuick 2.1
import QtQuick.Controls 1.0
import com.captemulation.qphidget.mock 1.0

Rectangle {
    width: 400
    height: 400

    Mock888Device {
        id: ifk

        input0: upstairs.fan
        input1: upstairs.cooling
        input2: upstairs.heating
        input4: downstairs.fan
        input5: downstairs.cooling
        input6: downstairs.heating
    }



    Column {
        id: column1
        anchors.fill: parent
        spacing: 12

        Zone {
            id: upstairs
        }

        Zone {
            id: downstairs
        }
    }


}
