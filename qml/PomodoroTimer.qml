import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.4

Popup {
    id: pomodoroTimer

    modal: false
    focus: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    property string task;

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
                text: "25:00"

                font.weight: Font.Bold
                font.pointSize: 22
            }

            Button {
                text: qsTr("Start")
                font.pointSize: 14

                icon.source: "qrc:/img/start_timer.svg"
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
    }
}
