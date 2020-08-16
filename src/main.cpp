#include <QApplication>
#include <QQuickView>
#include <QQuickItem>
#include <QWidget>
#include <QQmlEngine>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("#100DaysOfCode");

    QApplication app(argc, argv);

    QQuickView view;
    view.connect(view.engine(), &QQmlEngine::quit, &app, &QCoreApplication::quit);
    view.setSource(QUrl(QStringLiteral("qrc:/qml/MainWindow.qml")));
    if (view.status() == QQuickView::Error) {
        return -1;
    }

    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.show();
    return app.exec();
}
