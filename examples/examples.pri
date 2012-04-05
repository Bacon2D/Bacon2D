CONFIG += qt

contains(QT_VERSION, ^5.*) QT += quick
else: QT += declarative

TEMPLATE = app

SOURCES += $$PWD/launcher/main.cpp

HEADERS += $$PWD/launcher/launcher.h

RESOURCES += $$PWD/launcher/launcher.qrc

exists($$OUT_PWD/resources.qrc)
    RESOURCES += $$OUT_PWD/resources.qrc
