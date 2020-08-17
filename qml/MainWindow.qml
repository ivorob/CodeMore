import QtQuick 2.4

Rectangle {
    width: 800
    height: 640
    color: "white"

    Component {
        id: todoListDelegate

        Rectangle {
            id: todoListItem
            width: 200; height: 40;
            color: "white"

            MouseArea {
                id: todoListItemMouseArea
                anchors.fill: parent
                hoverEnabled: true

                onEntered: {
                    todoListItem.color = "lightsteelblue";
                }

                onExited: {
                    todoListItem.color = "white"
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
        anchors.fill: parent

        model: TodoListModel {}
        delegate: todoListDelegate
        focus: true
    }
}
