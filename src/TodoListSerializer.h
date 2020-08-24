#pragma once

#include <QXmlStreamWriter>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>

class TodoListSerializer {
public:
    void write(QXmlStreamWriter& writer, const QString& itemsJson, const QString& dataJson) const;
private:
    QJsonObject parseDataJson(const QString& dataJson) const;

    QString obtainJsonField(const QJsonValue& value, const QString& name) const;
};
