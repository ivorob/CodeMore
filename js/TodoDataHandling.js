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
            expectationsControl.text,
            realityControl.text)

        viewId.currentItem.color = root.color
        viewId.currentIndex = newDay

        viewId.currentItem.color = "lightsteelblue"
    }
}
