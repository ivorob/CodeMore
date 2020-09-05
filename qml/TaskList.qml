import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.4
import "qrc:/js/InternalDataController.js" as InternalDataController
import "qrc:/js/Dialogs.js" as Dialogs

Rectangle {
    property var title;
    property var dataModel;

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 30

            Text {
                text: title
            }

            Rectangle {
                Layout.fillWidth: true
            }

            RoundButton {
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

                text: "\uff0b"

                onClicked: {
                    var dialog = Dialogs.openNewTaskDialog(root)
                    if (dialog) {
                        var newTaskCreated = function() {
                            dataModel.append({
                                "task": dialog.taskTitle,
                                "description" : dialog.taskDescription
                            });
                            taskListView.currentIndex = dataModel.count - 1

                            InternalDataController.newChanges()
                        }

                        dialog.accepted.connect(newTaskCreated)
                    }
                }
            }
        }

        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true

            border.width: 1
            border.color: "#ccc"

            ListView {
                id: taskListView

                anchors.margins: 3, 3, 3, 3
                anchors.fill: parent
                focus: true
                snapMode: ListView.SnapOneItem

                delegate: Rectangle {
                    height: 20
                    width: parent.width
                    color: ListView.isCurrentItem ? "lightsteelblue" : root.color

                    Text {
                        anchors.left: parent.left
                        anchors.leftMargin: 3
                        anchors.verticalCenter: parent.verticalCenter
                        text: task
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: taskListView.currentIndex = index

                        onDoubleClicked: {
                            var dialog = Dialogs.openEditTaskDialog(root, task, description)
                            if (dialog) {
                                var taskChanged = function() {
                                    task = dialog.taskTitle
                                    description = dialog.taskDescription

                                    InternalDataController.newChanges()
                                }

                                dialog.accepted.connect(taskChanged)
                            }
                        }
                    }
                }

                model: dataModel
            }
        }
    }
}
