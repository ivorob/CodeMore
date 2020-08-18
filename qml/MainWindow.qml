import QtQuick 2.4
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.4

Rectangle {
    id: root
    width: 800
    height: 640

    RowLayout {
        anchors.fill: parent
        spacing: 2

        Component {
            id: todoListDelegate

            Rectangle {
                id: todoListItem
                height: 40
                width: parent.width
                color: root.color

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
                        todoListItem.color = root.color
                    }

                    Column {
                        anchors.verticalCenter: todoListItemMouseArea.verticalCenter
                        Text { 
                            text: "<b>" + description + "</b>"
                        }
                    }
                }
            }
        }

        ListView {
            Layout.preferredWidth: parent.width / 3
            height: parent.height
            flickableDirection: Flickable.VerticalFlick
            boundsBehavior: Flickable.StopAtBounds
            clip: true
            
            model: TodoListModel {}
            delegate: todoListDelegate
            focus: true

            ScrollBar.vertical: ScrollBar {}
        }

        Rectangle {
            height: parent.height
            Layout.preferredWidth: parent.width * 2 / 3
            
            ColumnLayout {
                anchors.fill: parent
                spacing: 1
                anchors.bottomMargin: 3
                anchors.rightMargin: 4

                Text {
                    id: goalPlaceholder
                    anchors.topMargin: 10

                    Layout.fillWidth: true
                    Layout.preferredHeight: 40

                    text: qsTr("Day goals:")
                }

                TextArea {
                    id: goalDescription

                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    placeholderText: qsTr("Enter description")

                    background: Rectangle {
                        border.width: 1
                        border.color: goalDescription.activeFocus ? "#000000" : "#BDBEBF"
                    }
                }

                Button {
                    Layout.preferredHeight: 28
                    Layout.alignment: Qt.AlignRight

                    text: qsTr("Save")
                }
            }
        }
    }
}
