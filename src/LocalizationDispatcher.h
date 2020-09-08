#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QTranslator>
#include <QLocale>
#include <QHash>
#include <QString>

class LocalizationDispatcher : public QObject {
    Q_OBJECT
public:
    LocalizationDispatcher(QQmlEngine *engine, QLocale locale, QObject *parent = nullptr);

    Q_INVOKABLE QStringList getLanguages() const;
    
    Q_INVOKABLE QString getCurrentLanguage() const;
    Q_INVOKABLE void setCurrentLanguage(const QString& currentLanguage);
private:
    void fillLanguages(const QString& prefix, const QString& directory);
    void fillCurrentTranslation();
    void retranslate();
    void updateSettings();
private:
    QQmlEngine *engine;
    QTranslator *translator;
    QTranslator *systemTranslator;
    QHash<QString, QString> languages;
    QHash<QString, QString> currentTranslation;
    QString currentLanguage;
};
