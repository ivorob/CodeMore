import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.0

Dialog {
    id: newTaskDialog
    title: qsTr("New task")
    property var text;

    modality: Qt.WindowModal
    standardButtons: StandardButton.Ok | StandardButton.Cancel

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

            Layout.fillWidth: true
            Layout.minimumWidth: 150
            Layout.preferredHeight: 30

            placeholderText: qsTr("Task description")
        }
    }
}