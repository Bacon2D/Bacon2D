TEMPLATE = lib
CONFIG += qt plugin
QT += declarative

TARGET = qmlgameitemplugin

DEPENDPATH += .
INCLUDEPATH += .

HEADERS += gameitem.h gamescene.h quasigame.h quasigameplugins.h
SOURCES += gameitem.cpp gamescene.cpp quasigame.cpp
