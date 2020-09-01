#include <QCoreApplication>
#include <QDirIterator>
#include <QDebug>

#include "LocalizationDispatcher.h"

namespace {

const char *languagesTranslation[] =
{
    QT_TRANSLATE_NOOP("Languages", "English"),
    QT_TRANSLATE_NOOP("Languages", "Russian"),
    QT_TRANSLATE_NOOP("Languages", "Deutch")
};

}

LocalizationDispatcher::LocalizationDispatcher(QQmlEngine *engine, QLocale locale, QObject *parent)
    : QObject(parent),
      engine(engine),
      translator(new QTranslator(this)),
      currentLanguage("English")
{
    QString prefix = "CodeMore";
    QString translationDirectory = "translations";
    fillLanguages(prefix, translationDirectory);
    fillCurrentTranslation();

    setCurrentLanguage(QLocale::languageToString(locale.language()));
}

void
LocalizationDispatcher::fillLanguages(const QString& prefix, const QString& directory)
{
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
                languages[language] = regExp.cap(1);
            }
        }
    }
}

void
LocalizationDispatcher::fillCurrentTranslation()
{
    this->currentTranslation.clear();

    QHashIterator<QString, QString> it(this->languages);
    while (it.hasNext()) {
        it.next();

        this->currentTranslation[it.key()] = qApp->translate("Languages", it.key().toUtf8());
    }

    this->currentTranslation["English"] = qApp->translate("Languages", "English");
}

QStringList
LocalizationDispatcher::getLanguages() const
{
    QStringList result;

    QHashIterator<QString, QString> it(this->currentTranslation);
    while (it.hasNext()) {
        it.next();

        result << it.value();
    }

    return result;
}

QString
LocalizationDispatcher::getCurrentLanguage() const
{
    return this->currentTranslation.value(this->currentLanguage);
}

void
LocalizationDispatcher::setCurrentLanguage(const QString& language)
{
    QHashIterator<QString, QString> it(this->currentTranslation);
    while (it.hasNext()) {
        it.next();

        if (it.value() == language) {
            this->currentLanguage = it.key();

            retranslate();
        }
    }
}

void
LocalizationDispatcher::retranslate()
{
    QCoreApplication::removeTranslator(this->translator);

    if (this->currentLanguage != "English") {
        QLocale locale(this->languages.value(this->currentLanguage));

        QString prefix = "CodeMore";
        QString translationDirectory = "translations";
        if (translator->load(locale, prefix, "_", translationDirectory)) {
            QCoreApplication::installTranslator(translator);

            fillCurrentTranslation();
        } else {
            qDebug() << "Cannot load translation";
        }
    }

    engine->retranslate();
}
