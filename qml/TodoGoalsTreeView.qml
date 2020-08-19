import QtQuick 2.0
import QtQuick.Controls 1.4

TreeView {
    anchors.fill: parent

    TableViewColumn {
        role: "name_role"
        title: "Name"
    }

    TableViewColumn {
        role: "description_role"
        title: "Description"
    }

    Component.onCompleted: {
        var component = Qt.createComponent("qrc:/qml/TodoGoalsTreeModel.qml");
        if (component.status == Component.Ready) {
            var componentObject = component.createObject(root);
            if (componentObject) {
                model = componentObject.createObject(root);
                console.log("OK")
            }
        }
    }
}
