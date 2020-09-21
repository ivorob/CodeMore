#include <QApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTranslator>
#include <QFont>
#include <QDebug>

#include "BusinessLogic.h"
#include "LocalizationDispatcher.h"
#include "ThemeDispatcher.h"
#include "Settings.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("#100DaysOfCode");

    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/img/favicon.png"));

    QFont font = app.font();
    font.setPixelSize(11);
    app.setFont(font);

    Settings::read();

    QQmlApplicationEngine engine;

    LocalizationDispatcher localizator(&engine, Settings::instance().getCurrentLocale());
    engine.rootContext()->setContextProperty("localizator", &localizator);

    BusinessLogic businessLogic;
    engine.rootContext()->setContextProperty("businessLogic", &businessLogic);

    ThemeDispatcher themeDispatcher;
    engine.rootContext()->setContextProperty("themeDispatcher", &themeDispatcher);

    engine.load(QUrl(QStringLiteral("qrc:/qml/MainWindow.qml")));
    return app.exec();
}
