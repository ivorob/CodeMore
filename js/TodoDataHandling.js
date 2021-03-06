function addEmptyDataIfUndefined(goals, day)
{
    if (goals[day] === undefined) {
        goals[day] = {"expectations" : "", "reality" : ""};
    }
}

function keepData(goals, day, expectations, reality)
{
    addEmptyDataIfUndefined(goals, day)

    goals[day].expectations = expectations
    goals[day].reality = reality
}

function restoreData(goals, day)
{
    addEmptyDataIfUndefined(goals, day)

    return goals[day]
}

function updateTaskTime(goals, day, taskGUID, interval)
{
    if (day >= 0 && goals[day] !== undefined) {
        var changed = false
        var expectations = JSON.parse(goals[day].expectations)
        for (var i = 0; i < expectations.length; ++i) {
            if (expectations[i].guid == taskGUID) {
                expectations[i].time += interval
                changed = true
                break;
            }
        }

        if (changed) {
            goals[day].expectations = JSON.stringify(expectations)
        }
    }
}

function nextDay(viewId, newDay)
{
    var model = viewId.model
    if (newDay >= model.count) {
        newDay = model.count - 1
    }

    if (viewId.currentIndex != newDay)
    {
        TodoDataHandler.keepData(viewId.goals,
            viewId.currentIndex,
            TodoDataHandler.serializeTodoList(expectationsControl.dataModel),
            TodoDataHandler.serializeTodoList(realityControl.dataModel)
        )

        viewId.currentItem.color = root.color
        viewId.currentIndex = newDay

        viewId.currentItem.color = themeDispatcher.getStringProperty("todoListView", "selection.color")

        InternalDataController.newChanges()
    }
}

function updatePomodoros(viewId, count)
{
    if (count == 0) {
        return
    }

    var model = viewId.model
    if (model) {
        model.get(viewId.currentIndex).pomodoros += count
    }
}

function serializeTodoList(model)
{
    var dataModel = []
    for (var i = 0; i < model.count; ++i) {
        dataModel.push(model.get(i))
    }

    return JSON.stringify(dataModel)
}

function deserializeTodoList(model, text)
{
    model.clear()
    if (text.length != 0) {
        var dataModel = JSON.parse(text)
        for (var i = 0; i < dataModel.length; ++i) {
            if (dataModel[i].guid === undefined) {
                dataModel[i].guid = businessLogic.generateGUID()
            }

            if (dataModel[i].time == undefined) {
                dataModel[i].time = 0
            }

            model.append(dataModel[i])
        }
    }
}
