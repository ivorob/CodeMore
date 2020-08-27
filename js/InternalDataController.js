function saveToDisk(file) {
    if (isNewChanges()) {
        TodoDataHandler.keepData(todoListView.goals, 
            todoListView.currentIndex, 
            expectationsControl.text,
            realityControl.text)

        businessLogic.saveToFile(file, 
            JsonUtils.convertListModelToJson(todoListView.model),
            JSON.stringify(todoListView.goals));

        root.filename = file
        noChanges()
    }
}

function openFromDisk(file) {
    var json = JSON.parse(businessLogic.loadFromFile(file));
    if (json && json.length != 0) {
        todoListView.model.clear();
        resetGoalsData()

        var lastCompletedIndex = 0;
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
    var component = Qt.createComponent("qrc:/qml/TodoListModel.qml")
    if (component.status == Component.Ready) {
        var newModel = component.createObject(todoListView, {})
        if (newModel) {
            resetGoalsData()
            todoListView.model = newModel

            expectationsControl.clear()
            realityControl.clear()
            root.filename = ""
        }
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
