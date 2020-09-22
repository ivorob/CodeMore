#include <gtest/gtest.h>
#include <QBuffer>

#include "ThemeDispatcher.h"

TEST(ThemeDispatcher, getStringPropertyForInvalidOwnerTest)
{
    ThemeDispatcher themeDispatcher;
    ASSERT_EQ(QString(), themeDispatcher.getStringProperty("invalidOwner", "propertyName"));
}

TEST(ThemeDispatcher, getStringPropertyForInvalidPropertyNameTest)
{
    ThemeDispatcher themeDispatcher;
    ASSERT_EQ(QString(), themeDispatcher.getStringProperty("todoListView", "invalidPropertyName"));
}

TEST(ThemeDispatcher, getThemeNameTest)
{
    ThemeDispatcher themeDispatcher;
    ASSERT_EQ(QString("Default"), themeDispatcher.getThemeName());
}

TEST(ThemeDispatcher, setThemeNameTest)
{
    ThemeDispatcher themeDispatcher;
    themeDispatcher.setThemeName("Light");
    ASSERT_EQ(QString("Light"), themeDispatcher.getThemeName());
}

TEST(ThemeDispatcher, readStyleDataFromStream)
{
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    buffer.seek(0);
    buffer.write(
R"({
    "name" : "Light",
    "style" : {
        "root" : {
            "color" : "white"
        },
        "expectations" : {
            "color" : "white",
            "workzone" : {
                "color" : "white"
            },
            "selection" : {
                "color" : "lightsteelblue"
            }
        }
    }
})");
    buffer.seek(0);

    ThemeDispatcher themeDispatcher;
    ASSERT_TRUE(themeDispatcher.loadTheme(&buffer));
    ASSERT_EQ(QString("Light"), themeDispatcher.getThemeName());

    ASSERT_EQ(QString("white"), themeDispatcher.getStringProperty("root", "color"));

    ASSERT_EQ(QString("white"), themeDispatcher.getStringProperty("expectations", "color"));
    ASSERT_EQ(QString("white"), themeDispatcher.getStringProperty("expectations", "workzone.color"));
    ASSERT_EQ(QString("lightsteelblue"), themeDispatcher.getStringProperty("expectations", "selection.color"));
    ASSERT_EQ(QString(), themeDispatcher.getStringProperty("reality", "selection.color"));
}
