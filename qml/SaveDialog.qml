import QtQuick 2.0
import QtQuick.Dialogs 1.3

FileDialog {
    id: saveDialog
    title: qsTr("Save")
    folder: shortcuts.document
    nameFilters: [qsTr("Xml files (*.xml)"), qsTr("All files (*)") ]
    selectMultiple: false
    selectExisting: false

    onAccepted: {
        console.log("You choose: " + saveDialog.fileUrl)
        root.save(saveDialog.fileUrl)
    }

    onRejected: {
        console.log("Canceled")
    }

    Component.onCompleted: visible = true
}
