import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.4
import 'qrc:/js/PomodoroTimer.js' as PomodoroTimerHelper
import 'qrc:/js/TodoDataHandling.js' as TodoDataHandler

Popup {
    id: pomodoroTimer

    modal: false
    focus: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    property alias task : taskText.text;
    property string taskGUID;
    property int taskDay;

    property int pomodoroTime: 25 * 60
    property int breakTime: 5 * 60
    property int secondsToComplete: pomodoroTime
    property int timeToKeep: 10;
    property int state : 0;
    property int pomodoros: 0

    property alias taskTimer : taskTimer;
    property alias pomodoroTrigger: pomodoroTrigger;

    signal keepTime(int taskDay, string guid, int interval)
    signal closeTimer()

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
                id: timerDisplay
                text: PomodoroTimerHelper.secondsToTime(secondsToComplete)

                font.weight: Font.Bold
                font.pointSize: 22
            }

            Rectangle {
                id: timerDisplayBackground
                visible: false
            }

            CustomButton {
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
                id: taskText

                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 3
                width: parent.width
                elide: Text.ElideRight

                wrapMode: Text.NoWrap
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

                text: pomodoros + " " + qsTr("Pomodoros")
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
                    --pomodoroTimer.timeToKeep
                } else {
                    PomodoroTimerHelper.timeIsOver()
                }

                if (pomodoroTimer.timeToKeep == 0) {
                    pomodoroTimer.keepTime(taskDay, pomodoroTimer.taskGUID, 10)
                    pomodoroTimer.timeToKeep = 10
                }
            }
        }

        Timer {
            id: blinkTimer

            interval: 500
            running: false
            repeat: true

            onTriggered: {
                PomodoroTimerHelper.blinkTime()
            }
        }
    }
}
