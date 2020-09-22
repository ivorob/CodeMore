#include <QJsonDocument>
#include <QFile>

#include "ThemeDispatcher.h"

ThemeDispatcher::ThemeDispatcher(QObject *parent)
    : QObject(parent),
      themeName("Default")
{
    QFile themeFile(":/themes/Default.theme");
    if (themeFile.open(QIODevice::ReadOnly)) {
        loadTheme(&themeFile);
    }
}

QString
ThemeDispatcher::getThemeName() const
{
    return this->themeName;
}

void
ThemeDispatcher::setThemeName(const QString& name)
{
    this->themeName = name;
}

bool
ThemeDispatcher::loadTheme(QIODevice *device)
{
    if (device) {
        QJsonDocument document = QJsonDocument::fromJson(device->readAll());
        if (!document.isNull() && document.isObject()) {
            QJsonObject root = document.object();

            QString name;
            auto items = readThemeProperties(root, name);
            if (!items.isEmpty()) {
                setThemeName(name);

                themeItems = items;
            }

            return true;
        }
    }

    return false;
}

ThemeDispatcher::ThemeItems
ThemeDispatcher::readThemeProperties(const QJsonObject& root, QString& themeName) const
{
    QJsonValue name = root.value("name");
    if (name.isString()) {
        QJsonValue style = root.value("style");
        if (style.isObject()) {
            themeName = name.toString();
            return readStyleData(style.toObject());
        }
    }

    return {};
}

ThemeDispatcher::ThemeItems
ThemeDispatcher::readStyleData(const QJsonObject& style) const
{
    ThemeItems items;

    for (auto it = style.constBegin(); it != style.constEnd(); ++it)
    {
        const auto& value = it.value();
        if (value.isObject()) {
            readObject(items, it.key(), "", value.toObject());
        }
    }

    return items;
}

void
ThemeDispatcher::readObject(ThemeItems& items, const QString& id, const QString& key, const QJsonObject& currentObject) const
{
    for (auto it = currentObject.constBegin(); it != currentObject.constEnd(); ++it)
    {
        QString currentKey = it.key();
        if (!key.isEmpty()) {
            currentKey = key + "." + it.key();
        }

        const auto& value = it.value();
        if (value.isString()) {
            items[id].insert(currentKey, value.toString());
        } else if (value.isObject()) {
            readObject(items, id, currentKey, value.toObject());
        }
    }
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
