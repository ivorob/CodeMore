#include <QJsonDocument>
#include <QJsonArray>
#include <QVariant>

#include "TodoListSerializer.h"

void
TodoListSerializer::write(QXmlStreamWriter& writer, const QString& itemsJson, const QString& dataJson) const
{
    QJsonObject data = parseDataJson(dataJson);

    QJsonDocument document = QJsonDocument::fromJson(itemsJson.toUtf8());
    if (!document.isNull() && document.isArray()) {
        writer.writeStartDocument();

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

        writer.writeEndDocument();
    }
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
