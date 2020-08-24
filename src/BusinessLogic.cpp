#include <QFile>
#include <QXmlStreamWriter>
#include <QUrl>

#include "BusinessLogic.h"
#include "TodoListSerializer.h"

BusinessLogic::BusinessLogic(QObject *parent)
    : QObject(parent)
{
}

void
BusinessLogic::saveToFile(const QString& filename, const QString& treeJson, const QString& itemsJson) const
{
    QFile file(QUrl(filename).toLocalFile());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::NewOnly)) {
        return;
    }

    TodoListSerializer serializer;

    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.setAutoFormattingIndent(4);
    serializer.write(writer, treeJson, itemsJson);
}
