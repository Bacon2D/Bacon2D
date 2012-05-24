CONFIG += qt

contains(QT_VERSION, ^5.*) QT += quick
else: QT += declarative

TEMPLATE = app

SOURCES += $$PWD/launcher/main.cpp
HEADERS += $$PWD/launcher/launcher.h
RESOURCES += $$PWD/launcher/launcher.qrc

exists($$_PRO_FILE_PWD_/resources.qrc)
    RESOURCES += $$_PRO_FILE_PWD_/resources.qrc

# This is a workaround to force rebuild of resource files
# whenever a contained file changes
DEPENDPATH += $$OUT_PWD
