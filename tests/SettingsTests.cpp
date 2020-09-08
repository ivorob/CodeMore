#include <gtest/gtest.h>
#include <QBuffer>

#include "Settings.h"

TEST(Settings, currentLocaleTest)
{
    Settings settings;
    ASSERT_EQ(QLocale(), settings.getCurrentLocale());

    QLocale locale(QLocale::Czech);
    settings.setCurrentLocale(locale);
    ASSERT_EQ(locale, settings.getCurrentLocale());
}
TEST(Settings, saveSettingsToInvalidDevice)
{
    Settings settings;
    ASSERT_FALSE(settings.save(nullptr));
}

TEST(Settings, saveSettings)
{
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    buffer.seek(0);

    Settings settings;
    settings.setCurrentLocale(QLocale(QLocale::Czech));
    ASSERT_TRUE(settings.save(&buffer));

    buffer.seek(0);
    QByteArray data = buffer.readAll();
    ASSERT_EQ("{\n    \"currentLocale\": \"cs\"\n}\n", data);
}
TEST(Settings, readSettingsFromInvalidDevice)
{
    Settings settings;
    ASSERT_FALSE(settings.read(nullptr));
}

TEST(Settings, readSettingsInvalidLocale)
{
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    buffer.seek(0);
    buffer.write("{\n    \"currentLocale\": \"Russian\"\n}\n");
    buffer.seek(0);

    Settings settings;
    ASSERT_TRUE(settings.read(&buffer));
    ASSERT_EQ(QLocale::c(), settings.getCurrentLocale());
}

TEST(Settings, readSettings)
{
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    buffer.seek(0);
    buffer.write("{\n    \"currentLocale\": \"ru\"\n}\n");
    buffer.seek(0);

    Settings settings;
    ASSERT_TRUE(settings.read(&buffer));
    ASSERT_EQ(QLocale("ru"), settings.getCurrentLocale());
}
