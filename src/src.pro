TEMPLATE = lib
CONFIG += qt plugin
QT += quick

TARGET = quasigameplugins

DESTDIR = $$PWD/imports/QuasiGame
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
           layer.h \
           gamebasebackground.h \
           gamestaticbackground.h \
           gameanimatedbackground.h \
           util.h \
           viewport.h \
           box2ddebugdrawitem.h

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
           layer.cpp \
           gamebasebackground.cpp \
           gamestaticbackground.cpp \
           gameanimatedbackground.cpp \
           util.cpp \
           viewport.cpp \
           box2ddebugdrawitem.cpp

target.path = $$QT5PATH/imports/QuasiGame

qmlpluginfiles.path = $$target.path
qmlpluginfiles.files += $$OUT_PWD/imports/QuasiGame/*

INSTALLS += target qmlpluginfiles
