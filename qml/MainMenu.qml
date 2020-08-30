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
            shortcut: "Ctrl+N"

            onTriggered: root.newTodoList()
        }

        Action { 
            text: qsTr("&Open...")
            shortcut: "Ctrl+O"
        
            onTriggered: Dialogs.openOpenDialog(root)
        }

        Action { 
            text: qsTr("&Save")
            shortcut: "Ctrl+S"

            onTriggered: {
                if (root.filename.length == 0) {
                    Dialogs.openSaveDialog(root)
                } else {
                    root.save(root.filename)
                }
            }
        }

        Action { 
            text: qsTr("Save &As...")
            shortcut: "Ctrl+Shift+S"

            onTriggered: {
                openDialog("qrc:/qml/SaveDialog.qml", root)
            }
        }
        MenuSeparator {}
        Action { 
            text: qsTr("&Quit") 

            onTriggered: Qt.quit()
        }
    }

    Menu {
        title: qsTr("&Language")

        Action {
            text: qsTr("&English")
        }
    }

    Menu {
        title: qsTr("&Help")

        Action { 
            text: qsTr("&About")
            shortcut: "F1"

            onTriggered: Dialogs.openAboutDialog(root)
        }
    }
}
