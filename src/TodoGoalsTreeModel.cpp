#include "TodoGoalsTreeModel.h"

TodoGoalsTreeModel::TodoGoalsTreeModel(QObject *parent)
    : QStandardItemModel(parent)
{
    init();
}

QHash<int, QByteArray>
TodoGoalsTreeModel::roleNames() const
{
    return roles;
}

void
TodoGoalsTreeModel::init()
{
    roles[Qt::DisplayRole] = "name_role";
    roles[Qt::WhatsThisRole] = "description_role";

    auto firstRoot = new QStandardItem("First");
    auto child1 = new QStandardItem("child 1");
    child1->setData("Child 1 description", Qt::WhatsThisRole);
    auto child2 = new QStandardItem("child 2");
    child2->setData("Child 2 description", Qt::WhatsThisRole);
    firstRoot->appendRow(child1);
    firstRoot->appendRow(child2);

    appendRow(firstRoot);
}
