function saveToDisk(file) {
    TodoDataHandler.keepData(todoListView.goals,
        todoListView.currentIndex,
        TodoDataHandler.serializeTodoList(expectationsControl.dataModel),
        TodoDataHandler.serializeTodoList(realityControl.dataModel))

    businessLogic.saveToFile(file,
        JsonUtils.convertListModelToJson(todoListView.model),
        JSON.stringify(todoListView.goals));

    root.filename = file
    noChanges()
}

function openFromDisk(file) {
    var json = JSON.parse(businessLogic.loadFromFile(file));
    if (json && json.length != 0) {
        todoListView.model.clear();
        resetGoalsData()

        var lastCompletedIndex = -1;
        for (var i = 0; i < json.length; ++i) {
            var currentDay = parseInt(json[i].index)

            todoListView.model.append({
                "day" : currentDay,
                "itemState" : parseInt(json[i].state)
            })

            TodoDataHandler.keepData(todoListView.goals, currentDay - 1, json[i].expectations, json[i].reality)

            if (parseInt(json[i].state)) {
                lastCompletedIndex = i;
            }
        }

        if (lastCompletedIndex + 1 < json.length) {
            ++lastCompletedIndex
        }

        console.log("index: " + lastCompletedIndex)
        todoListView.currentIndex = lastCompletedIndex

        root.filename = file
        noChanges()
    }
}

function newTodoList() {
    console.log("new todo list")

    var newTodoListHandler = function() {
        var component = Qt.createComponent("qrc:/qml/TodoListModel.qml")
        if (component.status == Component.Ready) {
            var newModel = component.createObject(todoListView, {})
            if (newModel) {
                resetGoalsData()
                todoListView.model = newModel

                expectationsControl.dataModel.clear()
                realityControl.dataModel.clear()
                root.filename = ""

                closeTimer()
            }
        }
    }

    if (isNewChanges()) {
        var dialog = Dialogs.openSaveChangesDialog(root)

        dialog.no.connect(newTodoListHandler)
        dialog.accepted.connect(newTodoListHandler)
    } else {
        newTodoListHandler()
    }
}

function closeTimer()
{
    if (expectationsControl.pomodoroTimer) {
        expectationsControl.pomodoroTimer.closeTimer()
        expectationsControl.pomodoroTimer.visible = false
        expectationsControl.pomodoroTimerButton.enabled = false
    }
}

function resetGoalsData()
{
    todoListView.goals = {}
    noChanges()
}

function newChanges()
{
    root.changes = true
}

function noChanges()
{
    root.changes = false
}

function isNewChanges()
{
    return root.changes
}

function closeApplication()
{
    var closeApplicationHandler = function() {
        Qt.quit()
    }

    if (isNewChanges()) {
        var dialog = Dialogs.openSaveChangesDialog(root)

        dialog.no.connect(closeApplicationHandler)
        dialog.accepted.connect(closeApplicationHandler)
    } else {
        closeApplicationHandler()
    }
}

function openFile()
{
    var openFileDialog = function() {
        var dialog = Dialogs.openOpenDialog(root)

        dialog.accepted.connect(closeTimer)
    }

    if (isNewChanges()) {
        var dialog = Dialogs.openSaveChangesDialog(root)

        dialog.no.connect(openFileDialog)
        dialog.accepted.connect(openFileDialog)
    } else {
        openFileDialog()
    }
}

function approveTask(item)
{
    realityControl.dataModel.append({
        "task" : qsTr("Completed: ") + item.task,
        "description" : item.description
    })

    realityControl.newIndex(realityControl.dataModel.count - 1)
}

function failTask(item)
{
    realityControl.dataModel.append({
        "task" : qsTr("Failed: ") + item.task,
        "description" : item.description
    })

    realityControl.newIndex(realityControl.dataModel.count - 1)
}

function updateTime(taskDay, guid, interval)
{
    if (taskDay != todoListView.currentIndex + 1) {
        TodoDataHandler.updateTaskTime(todoListView.goals, taskDay - 1, guid, interval)
    } else {
        var dataModel = expectationsControl.dataModel
        for (var i = 0; i < dataModel.count; ++i) {
            var item = dataModel.get(i)
            if (item.guid == guid) {
                item.time += interval

                newChanges()
                break;
            }
        }
    }
}
