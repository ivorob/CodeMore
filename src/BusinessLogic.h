#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QTranslator>

class BusinessLogic : public QObject {
    Q_OBJECT
public:
    BusinessLogic(QObject *parent = nullptr);

    Q_INVOKABLE void saveToFile(const QString& filename, const QString& treeJson, const QString& itemsJson) const;
    Q_INVOKABLE QString loadFromFile(const QString& filename) const;
    Q_INVOKABLE QString generateGUID() const;
};
