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
