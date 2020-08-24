#pragma once

#include <QObject>

class BusinessLogic : public QObject {
    Q_OBJECT
public:
    BusinessLogic(QObject *parent = nullptr);

    Q_INVOKABLE void saveToFile(const QString& filename, const QString& treeJson, const QString& itemsJson) const;
};
