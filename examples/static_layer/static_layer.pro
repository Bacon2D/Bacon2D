CONFIG += qt

contains(QT_VERSION, ^5.*) QT += quick
else: QT += declarative

TEMPLATE = app
TARGET = static_layer
DEPENDPATH += .
INCLUDEPATH += .

SOURCES += ../launcher/main.cpp
