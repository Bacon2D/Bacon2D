CONFIG += qt

QT += quick

contains(USE_OPENGL, 1) {
    QT += opengl
}

TEMPLATE = app

SOURCES += $$PWD/launcher/main.cpp
HEADERS += $$PWD/launcher/launcher.h
RESOURCES += $$PWD/launcher/launcher.qrc

exists($$_PRO_FILE_PWD_/resources.qrc)
    RESOURCES += $$_PRO_FILE_PWD_/resources.qrc

# This is a workaround to force rebuild of resource files
# whenever a contained file changes
DEPENDPATH += $$OUT_PWD
