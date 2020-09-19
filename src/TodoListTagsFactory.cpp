#include "TodoListTagsFactory.h"

namespace {

QMap<QString, QString> supportedTags = {
    { "itemState",      "state" },
    { "day",            "index" },
    { "pomodoros",      "pomodoros" },
    { "expectations",   "expectations" },
    { "reality",        "reality" }
};

}

QMap<QString, QString>
TodoListTagsFactory::getSupportedTags() const
{
    return supportedTags;
}
