#include <gtest/gtest.h>
#include <QBuffer>

#include "Settings.h"

TEST(Settings, currentLocaleTest)
{
    ASSERT_EQ(QLocale(), Settings::instance().getCurrentLocale());

    QLocale locale(QLocale::Czech);
    Settings::instance().setCurrentLocale(locale);
    ASSERT_EQ(locale, Settings::instance().getCurrentLocale());
}
TEST(Settings, saveSettingsToInvalidDevice)
{
    ASSERT_FALSE(Settings::instance().save(nullptr));
}

TEST(Settings, saveSettings)
{
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    buffer.seek(0);

    ASSERT_TRUE(Settings::instance().save(&buffer));

    buffer.seek(0);
    QByteArray data = buffer.readAll();
    ASSERT_EQ("{\n    \"currentLocale\": \"Czech\"\n}\n", data);
}

/*TEST(Settings, openSettings)
{
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    buffer.seek(0);
    buffer.write("{\n    \"currentLocale\": \"Russian\"\n}\n");

    ASSERT_TRUE(Settings::instance().open(&buffer));
    ASSERT_EQ(QLocale(), 
}*/
