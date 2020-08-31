#pragma once

#include <QStringList>

namespace Localization {

QStringList fillLanguages(const QString& prefix, const QString& directory);
QString getCurrentLanguage();

}
