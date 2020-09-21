#include <gtest/gtest.h>

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

TEST(ThemeDispatcher, getStringPropertyTest)
{
    ThemeDispatcher themeDispatcher;
    ASSERT_EQ(QString("lightsteelblue"), themeDispatcher.getStringProperty("todoListView", "selection.color"));

    ASSERT_EQ(QString("white"), themeDispatcher.getStringProperty("root", "color"));

    ASSERT_EQ(QString("white"), themeDispatcher.getStringProperty("expectations", "color"));
    ASSERT_EQ(QString("white"), themeDispatcher.getStringProperty("expectations", "workzone.color"));
    ASSERT_EQ(QString("lightsteelblue"), themeDispatcher.getStringProperty("expectations", "selection.color"));

    ASSERT_EQ(QString("white"), themeDispatcher.getStringProperty("expectations", "color"));
    ASSERT_EQ(QString("white"), themeDispatcher.getStringProperty("expectations", "workzone.color"));
    ASSERT_EQ(QString("lightsteelblue"), themeDispatcher.getStringProperty("expectations", "selection.color"));
}
