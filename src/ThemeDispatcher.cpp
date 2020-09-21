#include "ThemeDispatcher.h"

ThemeDispatcher::ThemeDispatcher(QObject *parent)
    : QObject(parent)
{
    auto& todoListView = themeItems["todoListView"];
    todoListView.insert("selection.color", "lightsteelblue");

    auto& root = themeItems["root"];
    root.insert("color", "white");

    auto& expectations = themeItems["expectations"];
    expectations.insert("color", "white");
    expectations.insert("selection.color", "lightsteelblue");
    expectations.insert("workzone.color", "white");
    //context menu
    expectations.insert("contextMenu.color", "white");
    expectations.insert("contextMenu.border", "black");
    expectations.insert("contextMenu.selection.color", "#F5F5F5");
    expectations.insert("contextMenu.textColor", "black");

    auto& reality = themeItems["reality"];
    reality.insert("color", "white");
    reality.insert("selection.color", "lightsteelblue");
    reality.insert("workzone.color", "white");
    //context menu
    reality.insert("contextMenu.color", "white");
    reality.insert("contextMenu.border", "black");
    reality.insert("contextMenu.selection.color", "#F5F5F5");
    reality.insert("contextMenu.textColor", "black");

    auto& fileMenu = themeItems["fileMenu"];
    fileMenu.insert("color", "white");
    fileMenu.insert("border", "black");
    fileMenu.insert("selection.color", "#F5F5F5");
    fileMenu.insert("textColor", "black");

    auto& languageMenu = themeItems["languageMenu"];
    languageMenu.insert("color", "white");
    languageMenu.insert("border", "black");
    languageMenu.insert("selection.color", "#F5F5F5");
    languageMenu.insert("textColor", "black");

    auto& helpMenu = themeItems["helpMenu"];
    helpMenu.insert("color", "white");
    helpMenu.insert("border", "black");
    helpMenu.insert("selection.color", "#F5F5F5");
    helpMenu.insert("textColor", "black");
}

QString
ThemeDispatcher::getStringProperty(const QString& ownerId, const QString& name) const
{
    if (!themeItems.count(ownerId)) {
        return {};
    }

    const auto& properties = themeItems[ownerId];
    if (!properties.count(name)) {
        return {};
    }

    return properties.value(name);
}
