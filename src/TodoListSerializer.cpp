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

                auto dayItems = obtainJsonFields(item);
                if (!dayItems.isEmpty() && dayItems.count("index") != 0)
                {
                    writer.writeStartElement("day");

                    auto day = dayItems.value("index");
                    int dayIndex = day.toInt();
                    QJsonValue dayDataValue = data.value(QString("%1").arg(dayIndex - 1));
                    auto taskItems = obtainJsonFields(dayDataValue);

                    writeDayItems(writer, dayItems);
                    writeDayItems(writer, taskItems);

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

QMap<QString, QString>
TodoListSerializer::obtainJsonFields(const QJsonValue& dayDataValue) const
{
    QMap<QString, QString> fields;

    const auto& supportedTags = tagsFactory.getSupportedTags();
    QMap<QString, QString>::const_iterator it = supportedTags.cbegin();
    while (it != supportedTags.end()) {
        QString item = obtainJsonField(dayDataValue, it.key());
        if (!item.isEmpty()) {
            fields[it.value()] = item;
        }

        ++it;
    }

    return fields;
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

void
TodoListSerializer::writeDayItems(QXmlStreamWriter& writer, const QMap<QString, QString>& items) const
{
    QMap<QString, QString>::const_iterator it = items.cbegin();
    while (it != items.cend()) {
        writer.writeTextElement(it.key(), it.value());
        ++it;
    }
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
    const auto& supportedTags = tagsFactory.getSupportedTags();
    const auto tags = supportedTags.values();

    QJsonObject result;
    while (reader.readNextStartElement()) {
        QString tagName = reader.name().toString();
        if (tags.contains(tagName.toUtf8())) {
            result.insert(tagName.toUtf8(), reader.readElementText());
        } else {
            reader.raiseError(QObject::tr("Incorrect file"));
        }
    }

    return result;
}
