#include <QApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTranslator>
#include <QDebug>

#include "BusinessLogic.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("#100DaysOfCode");

    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/img/favicon.png"));

    QTranslator translator;
    if (translator.load(QLocale("ru"), "CodeMore", "_", "translations")) {
        QCoreApplication::installTranslator(&translator);
    } else {
        qDebug() << "Cannot load translation";
    }

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/MainWindow.qml")));

    BusinessLogic businessLogic;
    engine.rootContext()->setContextProperty("businessLogic", &businessLogic);
    return app.exec();
}
