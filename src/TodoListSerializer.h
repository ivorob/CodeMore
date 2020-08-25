#pragma once

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QString>

class TodoListSerializer {
public:
    void write(QXmlStreamWriter& writer, const QString& itemsJson, const QString& dataJson) const;
    QString read(QXmlStreamReader& reader) const;
private:
    QJsonObject parseDataJson(const QString& dataJson) const;
    QString obtainJsonField(const QJsonValue& value, const QString& name) const;

    QJsonArray readTodoList(QXmlStreamReader& reader) const;
    QJsonValue readDay(QXmlStreamReader& reader) const;
};
