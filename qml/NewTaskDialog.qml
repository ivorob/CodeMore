import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.0

Dialog {
    id: newTaskDialog
    title: qsTr("New task")
    modality: Qt.WindowModal
    standardButtons: StandardButton.Ok | StandardButton.Cancel
    width: 350

    property var taskTitle;
    property var taskDescription;

    onAccepted: {
        taskTitle = taskTitleInput.text
        taskDescription = taskDescriptionInput.text
    }

    ColumnLayout {
        anchors.fill: parent

        TextField {
            id: taskTitleInput
            selectByMouse: true

            Layout.fillWidth: true
            Layout.minimumWidth: 150
            Layout.preferredHeight: 30

            placeholderText: qsTr("Task")

            background: Rectangle {
                border.width: 1
                border.color: "lightgrey"
                radius: 3

                color: root.color
            }

            Component.onCompleted: {
                if (newTaskDialog.taskTitle !== undefined) {
                    text = newTaskDialog.taskTitle
                }
            }
        }

        Flickable {
            Layout.fillWidth: true
            Layout.minimumHeight: 150

            TextArea.flickable: TextArea {
                id: taskDescriptionInput
                anchors.fill: parent

                selectByMouse: true

                placeholderText: qsTr("Task description")
                wrapMode: TextArea.Wrap

                background: Rectangle {
                    border.width: 1
                    border.color: "lightgrey"
                    radius: 3

                    color: root.color
                }

                Component.onCompleted: {
                    if (newTaskDialog.taskDescription !== undefined) {
                        text = newTaskDialog.taskDescription
                    }
                }

            }

            ScrollBar.vertical: ScrollBar {}
        }
    }

    Component.onCompleted: {
        visible = true
        taskTitleInput.focus = true
    }
}
