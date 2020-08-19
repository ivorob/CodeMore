import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Dialogs 1.3

Dialog {
    id: aboutWindow
    title: qsTr("About")

    modality: Qt.WindowModal
    standardButtons: StandardButton.Ok

    onAccepted: console.log("accept")

    Image {
        source: "qrc:/img/logo.png"
    }
}
