#include <QCoreApplication>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <QUrl>
#include <QUuid>
#include <QDirIterator>

#include "BusinessLogic.h"
#include "TodoListSerializer.h"

BusinessLogic::BusinessLogic(QObject *parent)
    : QObject(parent),
      themeDispatcher(new ThemeDispatcher)
{
    initThemes();
}

void
BusinessLogic::saveToFile(const QString& filename, const QString& treeJson, const QString& itemsJson) const
{
    QFile file(QUrl(filename).toLocalFile());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        return;
    }

    TodoListSerializer serializer;

    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.setAutoFormattingIndent(4);
    serializer.write(writer, treeJson, itemsJson);
}

QString
BusinessLogic::loadFromFile(const QString& filename) const
{
    QFile file(QUrl(filename).toLocalFile());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text | QIODevice::ExistingOnly)) {
        return {};
    }

    TodoListSerializer serializer;

    QXmlStreamReader reader(&file);
    return serializer.read(reader);
}

QString
BusinessLogic::generateGUID() const
{
    return QUuid::createUuid().toString();
}

QStringList
BusinessLogic::getThemes() const
{
    return this->themes;
}

bool
BusinessLogic::setTheme(const QString& theme)
{
    if (themeDispatcher) {
        QString path;
        if (theme == "Default") {
            path = ":/themes/";
        } else {
            path = QCoreApplication::applicationDirPath() + "/themes/";
        }

        QFile themeFile(path + theme + ".theme");
        if (themeFile.open(QIODevice::ReadOnly | QIODevice::Text | QIODevice::ExistingOnly)) {
            return themeDispatcher->loadTheme(&themeFile);
        }
    }

    return false;
}

void
BusinessLogic::initThemes()
{
    this->themes = QStringList {"Default"};

    QDirIterator it(
            QCoreApplication::applicationDirPath() + "/themes",
            QStringList() << "*.theme");
    while (it.hasNext()) {
        it.next();

        const auto& fileInfo = it.fileInfo();
        this->themes << fileInfo.baseName();
    }
}

ThemeDispatcher *
BusinessLogic::getThemeDispatcher()
{
    return this->themeDispatcher.get();
}
