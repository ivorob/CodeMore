#include <QApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTranslator>
#include <QDebug>

#include "BusinessLogic.h"
#include "Localization.h"

using QHashType = QHash<QString, QString>;
Q_DECLARE_METATYPE(QHashType)

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("#100DaysOfCode");

    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/img/favicon.png"));

    QTranslator translator;
    if (translator.load(QLocale(), "CodeMore", "_", "translations")) {
        QCoreApplication::installTranslator(&translator);
    } else {
        qDebug() << "Cannot load translation";
    }

    QQmlApplicationEngine engine;
    QStringList languages = Localization::fillLanguages("CodeMore", "translations");
    engine.rootContext()->setContextProperty("languageList", languages);
    engine.rootContext()->setContextProperty("currentLanguage", Localization::getCurrentLanguage());

    BusinessLogic businessLogic;
    engine.rootContext()->setContextProperty("businessLogic", &businessLogic);

    engine.load(QUrl(QStringLiteral("qrc:/qml/MainWindow.qml")));
    return app.exec();
}
