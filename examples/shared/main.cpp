#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.addImportPath(app.applicationDirPath() + "/../../src/qml");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
