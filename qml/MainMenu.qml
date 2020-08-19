import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Controls.Styles 1.3

MenuBar {
    background: Rectangle {
        color: root.color
    }

    Menu {
        title: qsTr("&File")

        Action { text: qsTr("&New") }
        Action { text: qsTr("&Open...") }
        Action { text: qsTr("&Save") }
        Action { text: qsTr("Save &As...") }
        MenuSeparator {}
        Action { 
            text: qsTr("&Quit") 

            onTriggered: Qt.quit()
        }
    }

    Menu {
        title: qsTr("&Help")

        Action { 
            text: qsTr("&About")

            onTriggered: { 
                var component = Qt.createComponent("qrc:/qml/AboutWindow.qml");
                if (component.status == Component.Ready) {
                    var dialog = component.createObject(root)
                    if (dialog) {
                        dialog.open()
                    }
                }
            }
        }
    }
}
