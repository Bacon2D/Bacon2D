TEMPLATE = lib
CONFIG += qt plugin
QT += declarative

TARGET = quasigameplugins

DESTDIR = lib
OBJECTS_DIR = tmp
MOC_DIR = tmp

DEPENDPATH += .
INCLUDEPATH += .

HEADERS += gameitem.h gamescene.h quasigame.h quasigameplugins.h
SOURCES += gameitem.cpp gamescene.cpp quasigame.cpp
