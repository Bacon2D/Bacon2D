TEMPLATE = lib
CONFIG += qt plugin
QT += declarative

TARGET = quasigameplugins

DESTDIR = lib
OBJECTS_DIR = tmp
MOC_DIR = tmp

DEPENDPATH += .
INCLUDEPATH += .

HEADERS += gameitem.h gamescene.h quasigame.h quasigameplugins.h gamesprite.h spriteanimation.h spriteitem.h spriteanimationitem.h animationtransition.h animationchangeevent.h
SOURCES += gameitem.cpp gamescene.cpp quasigame.cpp quasigameplugins.cpp gamesprite.cpp spriteanimation.cpp spriteitem.cpp spriteanimationitem.cpp animationtransition.cpp

target.path += imports/QuasiGame

target.files = lib/*
target.files += qml/*
target.files += qmldir

INSTALLS += target
