import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Controls.Styles 1.3

MenuBar {
    background: Rectangle {
        color: root.color
    }

    function openDialog(dialogUrl, id)
    {
        console.log("open dialog: " + dialogUrl)

        var component = Qt.createComponent(dialogUrl)
        if (component.status == Component.Ready) {
            var dialog = component.createObject(id)
            if (dialog) {
                dialog.open()
            }
        }
    }

    Menu {
        title: qsTr("&File")

        Action { text: qsTr("&New") }
        Action { text: qsTr("&Open...") }
        Action { 
            text: qsTr("&Save")

            onTriggered: openDialog("qrc:/qml/SaveDialog.qml", root)
        }
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

            onTriggered: openDialog("qrc:/qml/AboutWindow.qml", root)
        }
    }
}
