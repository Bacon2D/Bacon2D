/**
 * Copyright (C) 2012 by INdT
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * @author Rodrigo Goncalves de Oliveira <rodrigo.goncalves@openbossa.org>
 * @author Roger Felipe Zanoni da Silva <roger.zanoni@openbossa.org>
 */

#include "launcher.h"

#include <QtCore/qglobal.h>

#include <QtGui/QGuiApplication>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlEngine>
#include <QtQuick/QQuickView>

#ifdef QT_OPENGL_LIB
#include <QtOpenGL/QGLWidget>
#endif

int main(int argc, char *argv[])
{
    QByteArray data = "1";
    qputenv("QML_IMPORT_TRACE", data);

    QGuiApplication app(argc, argv);
    QQuickView view;

    Launcher launcher;

    view.engine()->rootContext()->setContextProperty("launcher", &launcher);
    view.engine()->addImportPath("../../src/imports");

    view.setSource(QUrl("qrc:/main.qml"));

#ifdef QT_OPENGL_LIB
    view.setViewport(new QGLWidget);
#endif

    view.show();

    return app.exec();
}
