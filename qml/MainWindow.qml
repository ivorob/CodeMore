import QtQuick 2.4
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.4
import '../js/TodoDataHandling.js' as TodoDataHandler

ApplicationWindow {
    id: root
    width: 800
    height: 640
    title: qsTr("CodeMore")
    visible: true

    menuBar : MainMenu {}

    signal save(string files)

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
                                Layout.fillWidth: true

                                text: "<b>Day #" + day + "</b>"
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
                Layout.column: 1

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

                    root.save.connect(saveToDisk)
                }

                function saveToDisk(file) {
                    console.log("save to file: " + file)
                }
            }

            Rectangle {
                Layout.preferredHeight: parent.height
                Layout.preferredWidth: parent.width * 2 / 3 - 4
                Layout.row: 1
                Layout.column: 2
                
                ColumnLayout {
                    anchors.fill: parent
                    spacing: 2
                    anchors.bottomMargin: 3
                    anchors.rightMargin: 4

                    Text {
                        id: goalPlaceholder
                        anchors.topMargin: 10

                        Layout.fillWidth: true
                        Layout.preferredHeight: 40

                        text: qsTr("Day goals:")
                    }

                    ScrollView {
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        TextArea {
                            id: expectationsControl

                            placeholderText: qsTr("Expectations")

                            background: Rectangle {
                                border.width: 1
                                border.color: expectationsControl.activeFocus ? "#000000" : "#BDBEBF"
                            }
                        }
                    }

                    ScrollView {
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        TextArea {
                            id: realityControl

                            placeholderText: qsTr("Reality")

                            background: Rectangle {
                                border.width: 1
                                border.color: realityControl.activeFocus ? "#000000" : "#BDBEBF"
                            }
                        }
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
    }
}
