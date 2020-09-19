#pragma once

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QString>
#include <QMap>

#include "TodoListTagsFactory.h"

class TodoListSerializer {
public:
    void write(QXmlStreamWriter& writer, const QString& itemsJson, const QString& dataJson) const;
    QString read(QXmlStreamReader& reader) const;
private:
    QJsonObject parseDataJson(const QString& dataJson) const;
    QString obtainJsonField(const QJsonValue& value, const QString& name) const;
    QMap<QString, QString> obtainJsonFields(const QJsonValue& value) const;
    void writeDayItems(QXmlStreamWriter& writer, const QMap<QString, QString>& items) const;

    QJsonArray readTodoList(QXmlStreamReader& reader) const;
    QJsonValue readDay(QXmlStreamReader& reader) const;
private:
    TodoListTagsFactory tagsFactory;
};
