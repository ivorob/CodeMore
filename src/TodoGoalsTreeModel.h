#pragma once

#include <QStandardItemModel>

class TodoGoalsTreeModel : public QStandardItemModel {
    Q_OBJECT
public:
    explicit TodoGoalsTreeModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;
private:
    void init();
private:
    QHash<int, QByteArray> roles;
};
