#include <QCoreApplication>
#include <QDirIterator>
#include <QLocale>

#include "Localization.h"

namespace {

const char *languagesTranslation[] =
{
    QT_TRANSLATE_NOOP("Languages", "English"),
    QT_TRANSLATE_NOOP("Languages", "Russian"),
    QT_TRANSLATE_NOOP("Languages", "Deutch")
};

}

QStringList
Localization::fillLanguages(const QString& prefix, const QString& directory)
{
    QStringList languages = {qApp->translate("Languages", "English")};

    QString localizationDirectory = QCoreApplication::applicationDirPath() + "/" + directory;
    QDirIterator it(localizationDirectory, QStringList() << prefix + "_*.qm", QDir::NoFilter);
    while (it.hasNext()) {
        QString path = it.next();

        QRegExp regExp("\\/CodeMore_([a-z]{2}).qm");
        int position = regExp.indexIn(path);
        if (position > -1) {
            QLocale::Language languageCode = QLocale(regExp.cap(1)).language();
            QString language = QLocale::languageToString(languageCode);
            if (!language.isEmpty()) {
                languages << qApp->translate("Languages", language.toUtf8());
            }
        }
    }

    return languages;
}

QString
Localization::getCurrentLanguage()
{
    QLocale::Language languageCode = QLocale().language();
    QString currentLanguage = QLocale::languageToString(languageCode);
    return qApp->translate("Languages", currentLanguage.toUtf8());
}
