#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QtCore/QObject>
#include <QtCore/QFile>

#include <QtQml/QQmlContext>

class Launcher : public QObject
{
    Q_OBJECT

public:
    Launcher(QObject *parent = 0) : QObject(parent) {}

public slots:
    QString qmlData() const
    {
        QString import("import QuasiGame 1.0\n");
        import += "import QtQuick 2.0\n";
        QFile qmlFile(":/GameWindow.qml");
        if (!qmlFile.open(QIODevice::ReadOnly)) {
            qWarning("Error opening GameWindow.qml");
            return QString();
        }

        QByteArray qmlText = qmlFile.readAll();

        return import + qmlText;
    }
};

#endif
