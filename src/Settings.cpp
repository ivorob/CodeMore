#include <QJsonObject>
#include <QJsonDocument>
#include <QCoreApplication>
#include <QFile>
#include <QDir>

#include "Settings.h"

Settings::Settings()
{
}

void
Settings::setCurrentLocale(const QLocale& locale)
{
    this->currentLocale = locale;
}

QLocale
Settings::getCurrentLocale() const
{
    return this->currentLocale;
}

Settings&
Settings::instance()
{
    static Settings settings;
    return settings;
}

bool
Settings::save(QIODevice *device) const
{
    if (device) {
        QJsonObject settings;
        settings.insert("currentLocale", this->currentLocale.bcp47Name());

        QJsonDocument document(settings);
        return device->write(document.toJson()) > 0;
    }

    return false;
}

bool
Settings::read(QIODevice *device)
{
    if (device) {
        QJsonDocument document = QJsonDocument::fromJson(device->readAll());
        if (!document.isNull() && document.isObject()) {
            QJsonObject settings = document.object();
            readCurrentLocale(settings);

            return true;
        }
    }

    return false;
}

void
Settings::readCurrentLocale(const QJsonObject& settings)
{
    QJsonValue value = settings.value("currentLocale");
    if (!value.isNull()) {
        this->currentLocale = QLocale(value.toString());
    } else {
        this->currentLocale = QLocale();
    }
}

bool
Settings::read()
{
    QString path = getSettingsDirectoryPath() + "/settings.json";
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text | QIODevice::ExistingOnly)) {
        return false;
    }

    return Settings::instance().read(&file);
}

bool
Settings::write()
{
    QString applicationSettingsDirectory(getSettingsDirectoryPath());
    if (QDir().mkpath(applicationSettingsDirectory)) {
        QFile file(applicationSettingsDirectory + "/settings.json");
        if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
            return Settings::instance().save(&file);
        }
    }

    return false;
}

QString
Settings::getSettingsDirectoryPath()
{
    return QDir::homePath() + "/" + QCoreApplication::applicationName();
}
