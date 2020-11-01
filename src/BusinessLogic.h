#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QTranslator>
#include <QStringList>

#include "ThemeDispatcher.h"

class BusinessLogic : public QObject {
    Q_OBJECT
public:
    BusinessLogic(QObject *parent = nullptr);

    Q_INVOKABLE void saveToFile(const QString& filename, const QString& treeJson, const QString& itemsJson) const;
    Q_INVOKABLE QString loadFromFile(const QString& filename) const;
    Q_INVOKABLE QString generateGUID() const;

    Q_INVOKABLE QStringList getThemes() const;
    Q_INVOKABLE bool setTheme(const QString& theme);

    ThemeDispatcher *getThemeDispatcher();
private:
    void initThemes();
private:
    QStringList themes;
    QScopedPointer<ThemeDispatcher> themeDispatcher;
};
