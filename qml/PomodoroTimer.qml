import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.4

Popup {
    id: pomodoroTimer

    modal: false
    focus: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    property string task;
    property int secondsToComplete: 25 * 60

    function secondsToTime(timerSeconds) {
        var seconds = timerSeconds % 60
        var minutes = (timerSeconds - seconds) / 60

        var result = ((minutes < 10) ? "0" + minutes : minutes) + ":" +
               ((seconds < 10) ? "0" + seconds : seconds)
        return result
    }

    ColumnLayout {
        Text {
            text: qsTr("Pomodoro")

            font.weight: Font.Bold
            font.pointSize: 14
        }

        Text {
            text: qsTr("Time until break")
        }

        RowLayout {
            Layout.fillWidth: true

            Text {
                text: secondsToTime(secondsToComplete)

                font.weight: Font.Bold
                font.pointSize: 22
            }

            Button {
                id: pomodoroTrigger
                text: qsTr("Start")
                font.pointSize: 14

                icon.source: "qrc:/img/start_timer.svg"

                onClicked: {
                    text = qsTr("Stop")
                    icon.source = "qrc:/img/stop_timer.svg"

                    taskTimer.start()
                }
            }
        }

        Rectangle {
            Layout.preferredHeight: 10
        }

        Rectangle {
            Layout.preferredHeight: 30
            Layout.fillWidth: true

            color: "#F5F5F5"

            Text {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 3
                width: parent.width
                elide: Text.ElideRight

                wrapMode: Text.NoWrap

                text: task
            }
        }

        Rectangle {
            Layout.preferredHeight: 10
        }

        RowLayout {
            Layout.fillWidth: true

            Text {
                Layout.fillWidth: true

                text: qsTr("TODAY")
                font.weight: Font.Bold
                font.pointSize: 14
            }

            Text {
                Layout.fillWidth: true

                text: "0 " + qsTr("Pomodoros")
            }
        }

        Rectangle {
            Layout.preferredHeight: 10
        }

        Timer {
            id: taskTimer

            interval: 1000
            running: false
            repeat: true

            onTriggered: {
                console.log("triggered")
                if (pomodoroTimer.secondsToComplete != 0) {
                    --pomodoroTimer.secondsToComplete
                } else {
                    taskTimer.stop()
                    //pomodoroTrigger.text = qsTr("Take a brake")
                }
            }
        }
    }
}
