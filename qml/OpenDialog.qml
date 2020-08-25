import QtQuick 2.0
import QtQuick.Dialogs 1.3

FileDialog {
    id: openDialog
    title: qsTr("Open")
    folder: shortcuts.document
    nameFilters: [qsTr("Xml files (*.xml)"), qsTr("All files (*)") ]
    selectMultiple: false
    selectExisting: true

    onAccepted: {
        console.log("You choose: " + openDialog.fileUrl)
        root.open(openDialog.fileUrl)
    }

    onRejected: {
        console.log("Canceled")
    }

    Component.onCompleted: visible = true
}
