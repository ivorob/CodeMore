import QtQuick 2.0
import QtQuick.Controls 2.4

Button {
    property alias cursorShape : mouseArea.cursorShape

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true

        onPressed: mouse.accepted = false
        cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor
    }
}
