function secondsToTime(timerSeconds) {
    var seconds = timerSeconds % 60
    var minutes = (timerSeconds - seconds) / 60

    return ((minutes < 10) ? "0" + minutes : minutes) + ":" +
           ((seconds < 10) ? "0" + seconds : seconds)
}

function goToNextState()
{
    switch (pomodoroTimer.state) {
        case 0: //init state
            goToPomodoroState()
            break;
        case 1: //pomodoro state
            goToInitState()
            break;
        case 2: //take a break state
            goToBreakState()
            break;
        case 3:
            goToPomodoroState()
            break;
    }
}

function timeIsOver()
{
    switch (pomodoroTimer.state) {
        case 1:
            goToTakeBreakState()
            break;
        case 3:
            taskTimer.stop()
            break;
    }
}

function goToInitState()
{
    pomodoroTimer.blinkTimer.stop()
    pomodoroTimer.taskTimer.stop()

    pomodoroTimer.pomodoroTrigger.text = qsTr("Start")
    pomodoroTimer.pomodoroTrigger.icon.source = "qrc:/img/start_timer.svg"

    pomodoroTimer.secondsToComplete = pomodoroTimer.pomodoroTime
    pomodoroTimer.state = 0
}

function goToPomodoroState()
{
    pomodoroTimer.taskTimer.stop()

    pomodoroTimer.pomodoroTrigger.text = qsTr("Stop")
    pomodoroTimer.pomodoroTrigger.icon.source = "qrc:/img/stop_timer.svg"

    pomodoroTimer.state = 1;
    pomodoroTimer.secondsToComplete = pomodoroTimer.pomodoroTime

    pomodoroTimer.taskTimer.start()
}

function goToTakeBreakState()
{
    pomodoroTimer.taskTimer.stop()

    pomodoroTimer.pomodoroTrigger.text = qsTr("Break")
    pomodoroTimer.pomodoroTrigger.icon.source = "qrc:/img/pause_timer.svg"
    pomodoroTimer.pomodoros += 1

    pomodoroTimer.state = 2
    blinkTimer.start()

    TodoDataHandler.updatePomodoros(todoListView, 1)
}

function goToBreakState()
{
    blinkTimer.stop()
    showTime()

    pomodoroTimer.pomodoroTrigger.text = qsTr("Start")
    pomodoroTimer.pomodoroTrigger.icon.source = "qrc:/img/start_timer.svg"

    pomodoroTimer.secondsToComplete = pomodoroTimer.breakTime
    pomodoroTimer.state = 3

    pomodoroTimer.taskTimer.start()
}

function blinkTime()
{
    if (timerDisplayBackground.visible) {
        showTime()
    }  else {
        hideTime()
    }
}

function showTime()
{
    timerDisplayBackground.visible = false
    timerDisplay.visible = true
}

function hideTime()
{
    timerDisplayBackground.height = timerDisplay.height
    timerDisplayBackground.width = timerDisplay.width

    timerDisplayBackground.visible = true
    timerDisplay.visible = false
}

function openPomodoroTimer()
{
    var coordinares = pomodoroTimerButton.mapToItem(null,
        pomodoroTimerButton.width / 2, pomodoroTimerButton.height / 2)
    if (!pomodoroTimer) {
        pomodoroTimer = Dialogs.openPomodoroTimer(root, {
            x: coordinares.x,
            y: coordinares.y,
            task: qsTr("Day #") + todoListView.model.get(todoListView.currentIndex).day +
                ": " + dataModel.get(taskListView.currentIndex).task,
            taskGUID: dataModel.get(taskListView.currentIndex).guid,
            taskDay: todoListView.model.get(todoListView.currentIndex).day
        });
        if (pomodoroTimer) {
            pomodoroTimer.x -= pomodoroTimer.implicitWidth

            pomodoroTimer.keepTime.connect(function(taskDay, guid, interval) {
                if (pomodoroTimer.state == 1) { //pomodoro state
                    InternalDataController.updateTime(taskDay, guid, interval)
                }
            })
            pomodoroTimer.pomodoros = todoListView.model.get(todoListView.currentIndex).pomodoros
            pomodoroTimer.closeTimer.connect(goToInitState)
        }
    } else {
        pomodoroTimer.task = qsTr("Day #") + todoListView.model.get(todoListView.currentIndex).day +
                ": " + dataModel.get(taskListView.currentIndex).task
        pomodoroTimer.taskGUID = dataModel.get(taskListView.currentIndex).guid
        pomodoroTimer.pomodoros = todoListView.model.get(todoListView.currentIndex).pomodoros

        showPomodoroTimer(pomodoroTimer, coordinares.x, coordinares.y, pomodoroTimer.implicitWidth)
    }
}

function showPomodoroTimer(pomodoroTimer, x, y, width)
{
    pomodoroTimer.x = x - width
    pomodoroTimer.y = y

    pomodoroTimer.open()
}
