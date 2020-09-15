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
    taskTimer.stop()

    pomodoroTrigger.text = qsTr("Start")
    pomodoroTrigger.icon.source = "qrc:/img/start_timer.svg"

    pomodoroTimer.secondsToComplete = pomodoroTimer.pomodoroTime
    pomodoroTimer.state = 0
}

function goToPomodoroState()
{
    taskTimer.stop()

    pomodoroTrigger.text = qsTr("Stop")
    pomodoroTrigger.icon.source = "qrc:/img/stop_timer.svg"

    pomodoroTimer.state = 1;
    pomodoroTimer.secondsToComplete = pomodoroTimer.pomodoroTime

    taskTimer.start()
}

function goToTakeBreakState()
{
    taskTimer.stop()

    pomodoroTrigger.text = qsTr("Break")
    pomodoroTrigger.icon.source = "qrc:/img/pause_timer.svg"

    pomodoroTimer.state = 2
    blinkTimer.start()
}

function goToBreakState()
{
    blinkTimer.stop()
    showTime()

    pomodoroTrigger.text = qsTr("Start")
    pomodoroTrigger.icon.source = "qrc:/img/start_timer.svg"

    pomodoroTimer.secondsToComplete = pomodoroTimer.breakTime
    pomodoroTimer.state = 3

    taskTimer.start()
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
