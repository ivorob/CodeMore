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

}

TEST(TodoListSerializer, saveTest)
{
    TodoListSerializer serializer;

    QString data;
    QXmlStreamWriter stream(&data);
    stream.setAutoFormatting(true);
    stream.setAutoFormattingIndent(4);
    serializer.write(stream, itemsTreeJson(), dataJson());

    ASSERT_EQ(R"(<?xml version="1.0"?>
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
)", data.toStdString());
}
