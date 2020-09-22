#pragma once

#include <QObject>
#include <QMap>
#include <QString>
#include <QJsonObject>
#include <QIODevice>

class ThemeDispatcher : public QObject {
    Q_OBJECT
public:
    ThemeDispatcher(QObject *parent = nullptr);

    Q_INVOKABLE QString getStringProperty(const QString& ownerId, const QString& name) const;

    bool loadTheme(QIODevice *device);

    QString getThemeName() const;
    void setThemeName(const QString& name);
private:
    using ItemProperties = QMap<QString, QString>;
    using ThemeItems = QMap<QString, ItemProperties>;
private:
    ThemeItems readThemeProperties(const QJsonObject& root, QString& themeName) const;
    ThemeItems readStyleData(const QJsonObject& root) const;
    void readObject(ThemeItems& themeItems, const QString& id, const QString& key, const QJsonObject& currentObject) const;
private:
    ThemeItems themeItems;
    QString themeName;
};
