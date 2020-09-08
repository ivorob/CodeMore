#pragma once

#include <QLocale>
#include <QIODevice>
#include <QJsonObject>

class Settings {
public:
    Settings();

    void setCurrentLocale(const QLocale& locale);
    QLocale getCurrentLocale() const;

    bool save(QIODevice *device) const;
    bool read(QIODevice *device);
public:
    static Settings& instance();
    static bool read();
    static bool write();
private:
    void readCurrentLocale(const QJsonObject& settings);
private:
    QLocale currentLocale;
};
