function secondsToTime(timerSeconds) {
    var seconds = timerSeconds % 60
    var minutes = (timerSeconds - seconds) / 60

    return ((minutes < 10) ? "0" + minutes : minutes) + ":" +
           ((seconds < 10) ? "0" + seconds : seconds)
}

function goToNextState()
{
    switch (pomodoroTimer.state) {
        case 0: //before start
            goToPomodoroState()
            taskTimer.start()
            break;
        case 1:
            if (pomodoroTimer.secondsToComplete != 0) {
                taskTimer.stop()
                goToInitState()
            }
            break;
    }
}

function goToPomodoroState()
{
    pomodoroTrigger.text = qsTr("Stop")
    pomodoroTrigger.icon.source = "qrc:/img/stop_timer.svg"

    pomodoroTimer.state = 1;
}

function goToInitState()
{
    pomodoroTrigger.text = qsTr("Start")
    pomodoroTrigger.icon.source = "qrc:/img/start_timer.svg"

    pomodoroTimer.secondsToComplete = 25 * 60
    pomodoroTimer.state = 0
}
