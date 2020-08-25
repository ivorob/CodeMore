#include <QJsonDocument>
#include <QJsonArray>
#include <QVariant>
#include <QTextStream>

#include "TodoListSerializer.h"

void
TodoListSerializer::write(QXmlStreamWriter& writer, const QString& itemsJson, const QString& dataJson) const
{
    writer.writeStartDocument();
    writer.writeStartElement("todoList");

    QJsonObject data = parseDataJson(dataJson);
    QJsonDocument document = QJsonDocument::fromJson(itemsJson.toUtf8());
    if (!document.isNull() && document.isArray()) {
        QJsonArray items = document.array();
        for (const auto& item : items) {
            if (item.isObject()) {
                QJsonObject currentItem = item.toObject();
                QString itemState = obtainJsonField(item, "itemState");
                QString day = obtainJsonField(item, "day");
                if (!day.isEmpty() && !itemState.isEmpty())
                {
                    writer.writeStartElement("day");

                    writer.writeTextElement("index", day);
                    writer.writeTextElement("state", itemState);

                    int dayIndex = day.toInt();
                    QJsonValue dayDataValue = data.value(QString("%1").arg(dayIndex - 1));
                    QString expectations = obtainJsonField(dayDataValue, "expectations");
                    QString reality = obtainJsonField(dayDataValue, "reality");

                    writer.writeTextElement("expectations", expectations);
                    writer.writeTextElement("reality", reality);

                    writer.writeEndElement();
                }
            }
        }
    }

    writer.writeEndElement();
    writer.writeEndDocument();
}

QJsonObject
TodoListSerializer::parseDataJson(const QString& dataJson) const
{
    QJsonDocument doc = QJsonDocument::fromJson(dataJson.toUtf8());
    if (!doc.isNull() && doc.isObject()) {
        return doc.object();
    }

    return {};
}

QString
TodoListSerializer::obtainJsonField(const QJsonValue& dayDataValue, const QString& name) const
{
    if (dayDataValue.type() != QJsonValue::Undefined) {
        QJsonObject dayData = dayDataValue.toObject();

        QJsonValue field = dayData.value(name);
        if (field.type() != QJsonValue::Undefined) {
            return field.toVariant().toString();
        }
    }

    return {};
}

QString
TodoListSerializer::read(QXmlStreamReader& reader) const
{
    QJsonArray todoListJson;
    if (reader.readNextStartElement()) {
        if (reader.name() == "todoList") {
            todoListJson = readTodoList(reader);
        } else {
            reader.raiseError(QObject::tr("Incorrect file"));
        }
    }

    return reader.hasError() ? QString() : QJsonDocument(todoListJson).toJson(QJsonDocument::JsonFormat::Compact);
}

QJsonArray
TodoListSerializer::readTodoList(QXmlStreamReader& reader) const
{
    QJsonArray result;
    while (reader.readNextStartElement()) {
        if (reader.name() == "day") {
            result.append(readDay(reader));
        } else {
            reader.raiseError(QObject::tr("Incorrect file"));
        }
    }

    return result;
}

QJsonValue
TodoListSerializer::readDay(QXmlStreamReader& reader) const
{
    QJsonObject result;
    while (reader.readNextStartElement()) {
        if (reader.name() == "index") {
            result.insert("index", reader.readElementText());
        } else if (reader.name() == "state") {
            result.insert("state", reader.readElementText());
        } else if (reader.name() == "expectations") {
            result.insert("expectations", reader.readElementText());
        } else if (reader.name() == "reality") {
            result.insert("reality", reader.readElementText());
        } else {
            reader.raiseError(QObject::tr("Incorrect file"));
        }
    }

    return result;
}
