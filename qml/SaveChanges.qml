import QtQuick 2.0
import QtQuick.Dialogs 1.3
import "qrc:/js/Dialogs.js" as Dialogs

MessageDialog {
    id: saveChanges
    title: Qt.application.name

    modality: Qt.WindowModal
    standardButtons: StandardButton.Yes | StandardButton.No | StandardButton.Cancel
    icon: StandardIcon.Question

    onYes: {
        if (root.filename.length == 0) {
            var dialog = Dialogs.openSaveDialog(root)
            if (dialog) {
                dialog.accepted.connect(saveChanges.accepted)
            }
        } else {
            root.save(root.filename)
            saveChanges.accepted()
        }
    }

    text: qsTr("Do you want to save changes in current todo list?")
}
