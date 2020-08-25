#include <gtest/gtest.h>
#include <QXmlStreamWriter>

#include "TodoListSerializer.h"

namespace {

QString itemsTreeJson()
{
    return "[{\"itemState\":1,\"day\":1},{\"itemState\":0,\"day\":2},{\"itemState\":0,\"day\":7}]";
}

QString dataJson()
{
    return "{\"0\":{\"expectations\":\"- first task\",\"reality\":\"- first task: completed\"},\"1\":{\"expectations\":\"- some new task\",\"reality\":\"\"},\"6\":{\"expectations\":\"\",\"reality\":\"\"}}";
}

QString dataJson1()
{
    return "{\"0\":{\"expectations\":\"- first task\",\"reality\":\"- first task: completed\"},\"1\":{\"expectations\":\"- some new task\",\"reality\":\"\"},\"13\":{\"expectations\":\"\",\"reality\":\"\"}}";
}

}

TEST(TodoListSerializer, saveTest)
{
    TodoListSerializer serializer;

    QString data;
    QXmlStreamWriter writer(&data);
    writer.setAutoFormatting(true);
    writer.setAutoFormattingIndent(4);
    serializer.write(writer, itemsTreeJson(), dataJson());

    ASSERT_EQ(R"(<?xml version="1.0"?>
<todoList>
    <day>
        <index>1</index>
        <state>1</state>
        <expectations>- first task</expectations>
        <reality>- first task: completed</reality>
    </day>
    <day>
        <index>2</index>
        <state>0</state>
        <expectations>- some new task</expectations>
        <reality></reality>
    </day>
    <day>
        <index>7</index>
        <state>0</state>
        <expectations></expectations>
        <reality></reality>
    </day>
</todoList>
)", data.toStdString());
}

TEST(TodoListSerializer, unassignedDayDataSaveTest)
{
    TodoListSerializer serializer;

    QString data;
    QXmlStreamWriter writer(&data);
    writer.setAutoFormatting(true);
    writer.setAutoFormattingIndent(4);
    serializer.write(writer, itemsTreeJson(), dataJson1());

    ASSERT_EQ(R"(<?xml version="1.0"?>
<todoList>
    <day>
        <index>1</index>
        <state>1</state>
        <expectations>- first task</expectations>
        <reality>- first task: completed</reality>
    </day>
    <day>
        <index>2</index>
        <state>0</state>
        <expectations>- some new task</expectations>
        <reality></reality>
    </day>
    <day>
        <index>7</index>
        <state>0</state>
        <expectations></expectations>
        <reality></reality>
    </day>
</todoList>
)", data.toStdString());
}

TEST(TodoListSerializer, emptyDataSaveTest)
{
    TodoListSerializer serializer;

    QString data;
    QXmlStreamWriter writer(&data);
    writer.setAutoFormatting(true);
    writer.setAutoFormattingIndent(4);
    serializer.write(writer, {}, dataJson1());

    ASSERT_EQ(R"(<?xml version="1.0"?>
<todoList/>
)", data.toStdString());
}

TEST(TodoListSerializer, readTest)
{
    TodoListSerializer serializer;

    QString data = R"(<?xml version="1.0"?>
<todoList>
    <day>
        <index>1</index>
        <state>1</state>
        <expectations>- first task</expectations>
        <reality>- first task: completed</reality>
    </day>
    <day>
        <index>2</index>
        <state>0</state>
        <expectations>- some new task</expectations>
        <reality></reality>
    </day>
</todoList>
)";
    QXmlStreamReader reader(data);
    QString json = serializer.read(reader);
    ASSERT_FALSE(reader.hasError());
    ASSERT_EQ("[{\"expectations\":\"- first task\",\"index\":\"1\",\"reality\":\"- first task: completed\",\"state\":\"1\"},{\"expectations\":\"- some new task\",\"index\":\"2\",\"reality\":\"\",\"state\":\"0\"}]", json.toStdString());
}

TEST(TodoListSerializer, readNotXmlTest)
{
    TodoListSerializer serializer;

    QString data = "{}";
    QXmlStreamReader reader(data);
    QString json = serializer.read(reader);
    ASSERT_TRUE(reader.hasError());
    ASSERT_EQ("", json.toStdString());
}

TEST(TodoListSerializer, readInvalidXmlTest)
{
    TodoListSerializer serializer;

    QString data = R"(<?xml version="1.0"?>
<root/>
)";
    QXmlStreamReader reader(data);
    QString json = serializer.read(reader);
    ASSERT_TRUE(reader.hasError());
    ASSERT_EQ("", json.toStdString());
}
