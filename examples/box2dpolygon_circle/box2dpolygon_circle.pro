CONFIG += qt

contains(QT_VERSION, ^5.*) QT += quick
else: QT += declarative

TEMPLATE = app
TARGET = box2dpolygon_circle
DEPENDPATH += .
INCLUDEPATH += .

SOURCES += ../launcher/main.cpp
