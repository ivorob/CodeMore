#pragma once

#include <QMap>

class TodoListTagsFactory {
public:
    QMap<QString, QString> getSupportedTags() const;
};

