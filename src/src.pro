TEMPLATE = lib
CONFIG += qt plugin
QT += declarative quick #FIXME find a way to check for qt version to include declarative or quick

TARGET = quasigameplugins

DESTDIR = $$PWD/imports/QuasiGame
OBJECTS_DIR = tmp
MOC_DIR = tmp

DEPENDPATH += .
INCLUDEPATH += .

INCLUDEPATH += $$BOX2DPATH/include
LIBS += -L$$BOX2DPATH/lib -lBox2D

HEADERS += quasideclarativeitem.h \
           quasipainteditem.h \
           gameitem.h \
           gamescene.h \
           quasigame.h \
           quasigameplugins.h \
           spritesheet.h \
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
           staticlayer.h \
           animatedlayer.h \
           gamelayers.h \
           util.h \
           viewport.h \
           box2ddebugdrawitem.h \
           enums.h

SOURCES += gameitem.cpp \
           gamescene.cpp \
           quasigame.cpp \
           quasigameplugins.cpp \
           spritesheet.cpp \
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
           animatedlayer.cpp \
           staticlayer.cpp \
           gamelayers.cpp \
           util.cpp \
           viewport.cpp \
           box2ddebugdrawitem.cpp

target.path = $$QT5PATH/imports/QuasiGame

qmlpluginfiles.path = $$target.path
qmlpluginfiles.files += $$OUT_PWD/imports/QuasiGame/*

INSTALLS += target qmlpluginfiles
