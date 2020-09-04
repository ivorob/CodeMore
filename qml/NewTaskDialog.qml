import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.0

Dialog {
    id: newTaskDialog
    title: qsTr("New task")
    modality: Qt.WindowModal
    standardButtons: StandardButton.Ok | StandardButton.Cancel

    property var text;

    onAccepted: {
        text = textInput.text
    }

    RowLayout {
        anchors.fill: parent

        Text {
            Layout.minimumWidth: 50

            text: qsTr("Task")
        }

        TextField {
            id: textInput
            selectByMouse: true

            Layout.fillWidth: true
            Layout.minimumWidth: 150
            Layout.preferredHeight: 30

            placeholderText: qsTr("Task description")

            Component.onCompleted: {
                if (newTaskDialog.text !== undefined) {
                    text = newTaskDialog.text
                }
            }
        }
    }

    Component.onCompleted: {
        visible = true
        textInput.focus = true
    }
}
