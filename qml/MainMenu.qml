import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Controls.Styles 1.3
import QtQml 2.2
import "qrc:/js/Dialogs.js" as Dialogs

MenuBar {
    background: Rectangle {
        color: root.color
    }

    Menu {
        title: qsTr("&File")

        palette {
            window: themeDispatcher.getStringProperty("fileMenu", "color")
            dark: themeDispatcher.getStringProperty("fileMenu", "border")
            light: themeDispatcher.getStringProperty("fileMenu", "selection.color")
            windowText: themeDispatcher.getStringProperty("fileMenu", "textColor")
        }

        Action {
            text: qsTr("&New")
            shortcut: "Ctrl+N"

            onTriggered: root.newTodoList()
        }

        Action {
            text: qsTr("&Open...")
            shortcut: "Ctrl+O"

            onTriggered: root.openFile()
        }

        Action {
            text: qsTr("&Save")
            shortcut: "Ctrl+S"

            onTriggered: {
                if (root.filename.length == 0) {
                    Dialogs.openSaveDialog(root)
                } else {
                    root.save(root.filename)
                }
            }
        }

        Action {
            text: qsTr("Save &As...")
            shortcut: "Ctrl+Shift+S"

            onTriggered: {
                Dialogs.openSaveDialog(root)
            }
        }
        MenuSeparator {}
        Action {
            text: qsTr("&Quit")

            onTriggered: root.close()
        }
    }

    Menu {
        title: qsTr("&Language")

        palette {
            window: themeDispatcher.getStringProperty("languageMenu", "color")
            dark: themeDispatcher.getStringProperty("languageMenu", "border")
            light: themeDispatcher.getStringProperty("languageMenu", "selection.color")
            windowText: themeDispatcher.getStringProperty("languageMenu", "textColor")
        }

        Repeater {
            id: languagesMenu
            model: localizator.getLanguages()

            MenuItem {
                checkable: true
                checked: modelData == localizator.getCurrentLanguage()

                text : modelData

                onTriggered: {
                    var currentLanguage = localizator.getCurrentLanguage()
                    for (var i = 0; i < languagesMenu.model.length; ++i) {
                        var menuItem = languagesMenu.itemAt(i)
                        if (menuItem) {
                            menuItem.checked = menuItem.text == modelData

                            if (menuItem.checked && menuItem.text != currentLanguage) {
                                localizator.setCurrentLanguage(modelData)
                            }
                        }
                    }

                }
            }
        }
    }

    Menu {
        title: qsTr("&Themes")

        palette {
            window: themeDispatcher.getStringProperty("themesMenu", "color")
            dark: themeDispatcher.getStringProperty("themesMenu", "border")
            light: themeDispatcher.getStringProperty("themesMenu", "selection.color")
            windowText: themeDispatcher.getStringProperty("themesMenu", "textColor")
        }

        Repeater {
            id: themesMenu
            model: businessLogic.getThemes()

            MenuItem {
                checkable: true
                checked: modelData == themeDispatcher.getThemeName()

                text: modelData

                onTriggered: {
                    var currentTheme = themeDispatcher.getThemeName()
                    for (var i = 0; i < themesMenu.model.length; ++i) {
                        var themeItem = themesMenu.itemAt(i)
                        if (themeItem) {
                            themeItem.checked = themeItem.text == modelData

                            if (themeItem.checked && themeItem.text != currentTheme) {
                                if (!businessLogic.setTheme(modelData)) {
                                    console.log("Cannot load theme: " + modelData)
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Menu {
        title: qsTr("&Help")

        palette {
            window: themeDispatcher.getStringProperty("helpMenu", "color")
            dark: themeDispatcher.getStringProperty("helpMenu", "border")
            light: themeDispatcher.getStringProperty("helpMenu", "selection.color")
            windowText: themeDispatcher.getStringProperty("helpMenu", "textColor")
        }

        Action {
            text: qsTr("&About")
            shortcut: "F1"

            onTriggered: Dialogs.openAboutDialog(root)
        }
    }
}
