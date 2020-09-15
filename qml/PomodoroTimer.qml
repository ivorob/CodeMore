import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.4
import 'qrc:/js/PomodoroTimer.js' as PomodoroTimerHelper

Popup {
    id: pomodoroTimer

    modal: false
    focus: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    property string task;
    property int secondsToComplete: 25 * 60
    property int state : 0;

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
                text: PomodoroTimerHelper.secondsToTime(secondsToComplete)

                font.weight: Font.Bold
                font.pointSize: 22
            }

            Button {
                id: pomodoroTrigger
                text: qsTr("Start")
                font.pointSize: 14

                icon.source: "qrc:/img/start_timer.svg"

                onClicked: {
                    PomodoroTimerHelper.goToNextState();
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
