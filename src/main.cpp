#include <QApplication>
#include <QQmlApplicationEngine>

#include "TodoGoalsTreeModel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("#100DaysOfCode");

    QGuiApplication app(argc, argv);
    
    qmlRegisterType<TodoGoalsTreeModel>("CodeMore.Models", 0, 1, "TodoGoalsTreeModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/MainWindow.qml")));
    return app.exec();
}
