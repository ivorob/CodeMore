#pragma once

#include <QObject>
#include <QMap>
#include <QString>

class ThemeDispatcher : public QObject {
    Q_OBJECT
public:
    ThemeDispatcher(QObject *parent = nullptr);

    Q_INVOKABLE QString getStringProperty(const QString& ownerId, const QString& name) const;
private:
    using ItemProperties = QMap<QString, QString>;
    using ThemeItems = QMap<QString, ItemProperties>;
private:
    ThemeItems themeItems;
};
