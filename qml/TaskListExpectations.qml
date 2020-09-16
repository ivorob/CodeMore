import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.4
import "qrc:/js/InternalDataController.js" as InternalDataController
import "qrc:/js/Dialogs.js" as Dialogs

Rectangle {
    property var title;
    property var dataModel;

    signal approve(var task)
    signal fail(var task)

    function editTaskDialog(id, item) {
        var dialog = Dialogs.openEditTaskDialog(root, item.task, item.description)
        if (dialog) {
            var taskChanged = function() {
                item.task = dialog.taskTitle
                item.description = dialog.taskDescription

                InternalDataController.newChanges()
            }

            dialog.accepted.connect(taskChanged)
        }
    }

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

            CustomRoundButton {
                id: pomodoroTimerButton
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.preferredHeight: 25
                Layout.preferredWidth: 25
                enabled: false

                icon.source: "qrc:/img/pomodoro_timer.svg"

                onClicked: {
                    var coordinares = pomodoroTimerButton.mapToItem(null, 
                        pomodoroTimerButton.width / 2, pomodoroTimerButton.width / 2)
                    var dialog = Dialogs.openPomodoroTimer(root, {
                        x: coordinares.x,
                        y: coordinares.y,
                    });
                    if (dialog) {
                        dialog.x -= dialog.implicitWidth
                    }
                }
            }

            CustomRoundButton {
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.preferredHeight: 25
                Layout.preferredWidth: 25

                icon.source: "qrc:/img/plus.svg"

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
                        acceptedButtons: Qt.LeftButton | Qt.RightButton

                        onDoubleClicked: {
                            var item = dataModel.get(index)
                            if (item) {
                                editTaskDialog(root, item);
                            }
                        }

                        onClicked: {
                            if (mouse.button == Qt.LeftButton) {
                                taskListView.currentIndex = index
                            } else if (mouse.button == Qt.RightButton) {
                                taskListView.currentIndex = index
                                contextMenu.popup()
                            }
                        }

                        Menu {
                            id: contextMenu

                            MenuItem {
                                text: qsTr("Start timer")

                                icon.source: "qrc:/img/pomodoro_timer.svg"
                                onTriggered: {
                                    pomodoroTimerButton.enabled = true

                                    var coordinares = pomodoroTimerButton.mapToItem(null, 
                                        pomodoroTimerButton.width / 2, pomodoroTimerButton.height / 2)
                                    var dialog = Dialogs.openPomodoroTimer(root, {
                                        x: coordinares.x,
                                        y: coordinares.y,
                                        task: qsTr("Day #") + todoListView.model.get(todoListView.currentIndex).day + 
                                            ": " + dataModel.get(taskListView.currentIndex).task
                                    });
                                    if (dialog) {
                                        dialog.x -= dialog.implicitWidth
                                    }
                                }
                            }

                            MenuItem {
                                text: qsTr("Approve")
                                icon.source: "qrc:/img/approve.svg"

                                onTriggered: {
                                    var item = dataModel.get(index)
                                    if (item) {
                                        approve(item)
                                    }
                                }
                            }

                            MenuItem {
                                text: qsTr("Fail")
                                icon.source: "qrc:/img/fail.svg"

                                onTriggered: {
                                    var item = dataModel.get(index)
                                    if (item) {
                                        fail(item)
                                    }
                                }
                            }

                            MenuItem {
                                text: qsTr("Edit")
                                icon.source: "qrc:/img/edit.svg"

                                onTriggered: {
                                    var item = dataModel.get(index)
                                    if (item) {
                                        editTaskDialog(root, item)
                                    }
                                }
                            }

                            MenuItem {
                                text: qsTr("Copy")
                                icon.source: "qrc:/img/copy.svg"

                                onTriggered: {
                                    var item = dataModel.get(index)
                                    if (item) {
                                        dataModel.insert(index + 1, {
                                            "task": qsTr("Copy: ") + item.task,
                                            "description" : item.description
                                        });

                                        taskListView.currentIndex = index + 1
                                        InternalDataController.newChanges()
                                    }
                                }
                            }

                            MenuItem {
                                text: qsTr("Delete")
                                icon.source: "qrc:/img/delete.svg"

                                onTriggered: {
                                    dataModel.remove(index)

                                    InternalDataController.newChanges()
                                }
                            }
                        }
                    }
                }

                model: dataModel
            }
        }
    }
}
