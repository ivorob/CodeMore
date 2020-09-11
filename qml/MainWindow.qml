import QtQuick 2.4
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.4
import "qrc:/js/TodoDataHandling.js" as TodoDataHandler
import "qrc:/js/JsonUtils.js" as JsonUtils
import "qrc:/js/InternalDataController.js" as InternalDataController
import "qrc:/js/FileUtils.js" as FileUtils
import "qrc:/js/Dialogs.js" as Dialogs

ApplicationWindow {
    id: root
    width: 800
    height: 640
    title: {
        var result = qsTr("CodeMore")

        if (changes) {
            result = "*" + result;
        }

        if (filename.length != 0) {
            result += " - " + FileUtils.basename(filename)
        }

        return result
    }

    visible: true

    menuBar : MainMenu {}

    property bool changes: false
    property string filename: ""

    signal save(string file)
    signal open(string file)
    signal newTodoList()
    signal openFile()

    Rectangle {
        anchors.fill: parent

        GridLayout {
            anchors.fill: parent
            rows: 1
            columns: 2

            Component {
                id: todoListDelegate

                Rectangle {
                    id: todoListItem
                    height: 40
                    width: parent.width
                    color: todoListView.currentIndex == index ? "lightsteelblue" : root.color

                    Rectangle {
                        width: 1

                        color: "lightsteelblue"
                        anchors.right: parent.right
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                    }

                    MouseArea {
                        id: todoListItemMouseArea
                        anchors.fill: parent
                        hoverEnabled: true

                        onEntered: {
                            todoListItem.color = "lightsteelblue";
                        }

                        onExited: {
                            if (index != todoListView.currentIndex) {
                                todoListItem.color = root.color
                            }
                        }

                        onClicked: {
                            TodoDataHandler.nextDay(todoListView, index)
                        }

                        RowLayout {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.fill: parent

                            Text { 
                                Layout.leftMargin: 5
                                Layout.fillWidth: true

                                text: "<b>" + qsTr("Day #") + day + "</b>"
                            }

                            Image {
                                Layout.preferredWidth: 30
                                Layout.preferredHeight: 30
                                Layout.alignment: Qt.AlignRight

                                source: itemState != 0 ? "qrc:/img/completed.svg" : ""
                                fillMode: Image.PreserveAspectFit
                            }

                            Rectangle {
                                Layout.preferredWidth: 10
                            }
                        }
                    }
                }
            }

            ListView {
                id: todoListView

                property variant goals: { 0 : { "expectations" : "", "reality" : "" } }

                Layout.preferredWidth: parent.width / 3
                Layout.row: 1
                Layout.column: 0

                Layout.preferredHeight: parent.height
                flickableDirection: Flickable.VerticalFlick
                boundsBehavior: Flickable.StopAtBounds
                clip: true
                
                model: TodoListModel {}
                delegate: todoListDelegate
                focus: true

                ScrollBar.vertical: ScrollBar {}

                Component.onCompleted: {
                    for (var i = 0; i < model.count; ++i) {
                        if (model.get(i).itemState == 0) {
                            currentIndex = i
                            break
                        }
                    }

                    root.save.connect(InternalDataController.saveToDisk)
                    root.open.connect(InternalDataController.openFromDisk)
                }

                onCurrentItemChanged: {
                    var day = TodoDataHandler.restoreData(goals, currentIndex)
                    TodoDataHandler.deserializeTodoList(expectationsControl.dataModel, day.expectations)
                    TodoDataHandler.deserializeTodoList(realityControl.dataModel, day.reality)
                }
            }

            ColumnLayout {
                Layout.preferredHeight: parent.height
                Layout.preferredWidth: parent.width * 2 / 3 - 4
                Layout.bottomMargin: 3
                Layout.rightMargin: 3
                Layout.row: 1
                Layout.column: 1

                TaskListExpectations {
                    id: expectationsControl
                    title: qsTr("Expectations")

                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    dataModel: ListModel {}

                    Component.onCompleted: {
                        expectationsControl.approve.connect(InternalDataController.approveTask)
                        expectationsControl.fail.connect(InternalDataController.failTask)
                    }
                }

                TaskListReality {
                    id: realityControl
                    title: qsTr("Reality")

                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    dataModel: ListModel {}
                }

                Button {
                    Layout.preferredHeight: 28
                    Layout.alignment: Qt.AlignRight

                    text: qsTr("Next day")

                    onClicked: {
                        var model = todoListView.model
                        model.get(todoListView.currentIndex).itemState = 1

                        TodoDataHandler.nextDay(todoListView, todoListView.currentIndex + 1)
                    }
                }
            }
        }
    }

    onClosing: {
        close.accepted = false
        InternalDataController.closeApplication();
    }

    Component.onCompleted: {
        root.newTodoList.connect(InternalDataController.newTodoList)
        root.openFile.connect(InternalDataController.openFile)
    }
}
