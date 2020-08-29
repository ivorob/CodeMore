import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Controls.Styles 1.3
import "qrc:/js/Dialogs.js" as Dialogs

MenuBar {
    background: Rectangle {
        color: root.color
    }

    Menu {
        title: qsTr("&File")

        Action { 
            text: qsTr("&New")

            onTriggered: root.newTodoList()
        }
        Action { 
            text: qsTr("&Open...")
        
            onTriggered: Dialogs.openOpenDialog(root)
        }
        Action { 
            text: qsTr("&Save")

            onTriggered: {
                if (root.filename.length == 0) {
                    Dialogs.openSaveDialog(root)
                } else {
                    root.save(root.filename)
                }
            }
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

            onTriggered: Dialogs.openAboutDialog(root)
        }
    }
}
