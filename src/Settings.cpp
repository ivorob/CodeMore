#include <QJsonObject>
#include <QJsonDocument>

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
        settings.insert("currentLocale", QLocale::languageToString(this->currentLocale.language()));

        QJsonDocument document(settings);
        return device->write(document.toJson()) > 0;
    }

    return false;
}
