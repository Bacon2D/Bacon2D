#include <QGuiApplication>
#include <QQuickView>
#include <QDeclarativeEngine>
#include <QDir>

int main(int argc, char *argv[]) {
    QByteArray data = "1";
    qputenv("QML_IMPORT_TRACE", data);

    QGuiApplication app(argc, argv);

    QQuickView view;

    view.engine()->addImportPath("../../imports");

    view.setSource(QUrl::fromLocalFile("GameWindow.qml"));
    view.show();

    return app.exec();
}
