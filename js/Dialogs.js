function openDialog(dialogUrl, id)
{
    console.log("open dialog: " + dialogUrl)

    var component = Qt.createComponent(dialogUrl)
    if (component.status == Component.Error) {
        console.log(component.errorString())
    } else if (component.status == Component.Ready)
    {
        var dialog = component.createObject(id)
        if (dialog) {
            dialog.open()
            return dialog
        }
    }

    return null
}

function openSaveDialog(id)
{
    return openDialog("qrc:/qml/SaveDialog.qml", id)
}

function openOpenDialog(id)
{
    return openDialog("qrc:/qml/OpenDialog.qml", id)
}

function openAboutDialog(id)
{
    return openDialog("qrc:/qml/AboutWindow.qml", id)
}

function openSaveChangesDialog(id)
{
    return openDialog("qrc:/qml/SaveChanges.qml", id)
}

function openNewTaskDialog(id)
{
    return openDialog("qrc:/qml/NewTaskDialog.qml", id)
}
