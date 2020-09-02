import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.4
import "qrc:/js/InternalDataController.js" as InternalDataController
import "qrc:/js/Dialogs.js" as Dialogs

Rectangle {
    property var title;
    property var dataModel;

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 30

            Text {
                text: title
            }

            Rectangle {
                Layout.fillWidth: true
            }

            RoundButton {
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

                text: "\uff0b"

                onClicked: {
                    var dialog = Dialogs.openNewTaskDialog(root)
                    if (dialog) {
                        var newTaskCreated = function() {
                            dataModel.append({"task": dialog.text});

                            InternalDataController.newChanges()
                        }

                        dialog.accepted.connect(newTaskCreated)
                    }
                }
            }
        }

        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true

            border.width: 1
            border.color: "#ccc"

            ListView {
                anchors.fill: parent

                delegate: Text {
                    text: task
                }

                model: dataModel
            }
        }
    }
}
