#pragma once

#include <QLocale>
#include <QIODevice>

class Settings {
private:
    Settings();
public:
    void setCurrentLocale(const QLocale& locale);
    QLocale getCurrentLocale() const;

    bool save(QIODevice *device) const;
public:
    static Settings& instance();
private:
    QLocale currentLocale;
};
