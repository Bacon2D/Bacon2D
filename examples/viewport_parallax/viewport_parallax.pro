CONFIG += qt

contains(QT_VERSION, ^5.*) QT += quick
else: QT += declarative

TEMPLATE = app
TARGET = viewport_parallax
DEPENDPATH += .
INCLUDEPATH += .

SOURCES += ../launcher/main.cpp
