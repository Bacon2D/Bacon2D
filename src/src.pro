TEMPLATE = lib
CONFIG += qt plugin
QT += quick declarative

TARGET = quasigameplugins

DESTDIR = lib
OBJECTS_DIR = tmp
MOC_DIR = tmp

DEPENDPATH += .
INCLUDEPATH += .

INCLUDEPATH += $$BOX2DPATH/include
LIBS += -L$$BOX2DPATH/lib -lBox2D

HEADERS += gameitem.h \
           gamescene.h \
           quasigame.h \
           quasigameplugins.h \
           gamesprite.h \
           spriteanimation.h \
           spriteitem.h \
           spriteanimationitem.h \
           animationtransition.h \
           animationchangeevent.h \
           box2dscene.h \
           box2ditem.h \
           box2djointitem.h \
           box2dbaseitem.h \
           box2ddistancejointitem.h \
           box2dmousejointitem.h \
           gamebasebackground.h \
           gameanimatedbackground.h \
           util.h

SOURCES += gameitem.cpp \
           gamescene.cpp \
           quasigame.cpp \
           quasigameplugins.cpp \
           gamesprite.cpp \
           spriteanimation.cpp \
           spriteitem.cpp \
           spriteanimationitem.cpp \
           animationtransition.cpp \
           box2dscene.cpp \
           box2ditem.cpp \
           box2djointitem.cpp \
           box2dbaseitem.cpp \
           box2ddistancejointitem.cpp \
           box2dmousejointitem.cpp \
           gamebasebackground.cpp \
           gameanimatedbackground.cpp \
           util.cpp

target.path += imports/QuasiGame

target.files = lib/*
target.files += qml/*
target.files += qmldir

INSTALLS += target
