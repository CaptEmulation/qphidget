import QtQuick 2.0

Item {
    id: thermostat

    property real farenheit
    property bool isCoolingMode: false
    property bool isHeatingMode: false
    property real setPoint

    property int bounce: 2

    property bool heating: false
    property bool cooling: false
    property bool fan: false

    function execute() {
        if (isHeatingMode) {
            heating = heating ? farenheit < setPoint + bounce : farenheit < setPoint
        } else if (isCoolingMode) {
            cooling = cooling ? farenheit > setPoint - bounce : farenheit > setPoint
        }
    }

    onSetPointChanged: execute()

    onFarenheitChanged: execute()

    onCoolingChanged: {
        if (cooling) {
            fan = true
        } else if (!fanMotor.isFanOnMode) {
             fan = false
        }
    }

    onHeatingChanged: {
        if (heating) {
            fan = true
        } else if (!fanMotor.isFanOnMode) {
            fan = false
        }
    }

    state: 'off'

    states: [
        State {
            name: "cooling"
            PropertyChanges {
                target: thermostat
                isCoolingMode: true
                isHeatingMode: false
                heating: false
            }
        },

        State {
            name: "heating"
            PropertyChanges {
                target: thermostat
                isCoolingMode: false
                isHeatingMode: true
                cooling: false
            }
        },

        State {
            name: "off"
            PropertyChanges {
                target: thermostat
                isHeatingMode: false
                isCoolingMode: false
                heating: false
                cooling: false
            }
        }

    ]

    property Item fanMotor: fanMotor

    Item {
        id: fanMotor

        property bool isFanOnMode

        onIsFanOnModeChanged: {
            if (isFanOnMode) {
                thermostat.fan = true
            } else if (!(thermostat.heating || thermostat.cooling)) {
                thermostat.fan = false
            }
        }

        states: [
            State {
                name: "auto"
                PropertyChanges {
                    target: fanMotor
                    isFanOnMode: false
                }
            },

            State {
                name: "on"
                PropertyChanges {
                    target: fanMotor
                    isFanOnMode: true

                }
            }

        ]
    }

}
