TEMPLATE = lib
CONFIG += qt plugin

contains(QT_VERSION, ^5.*) QT += quick
else: QT += declarative

TARGET = quasigameplugin
TARGETPATH = QuasiGame

DESTDIR = $$OUT_PWD/imports/QuasiGame
OBJECTS_DIR = tmp
MOC_DIR = tmp

DEPENDPATH += .
INCLUDEPATH += .

INCLUDEPATH += $$BOX2DPATH/include
LIBS += -L$$BOX2DPATH/lib -lBox2D

HEADERS += quasideclarativeitem.h \
           quasipainteditem.h \
           entity.h \
           scene.h \
           game.h \
           plugins.h \
           spritesheet.h \
           sprite.h \
           spriteanimation.h \
           animationtransition.h \
           animationchangeevent.h \
           box2djointitem.h \
           box2dbaseitem.h \
           box2ddistancejointitem.h \
           box2dmousejointitem.h \
           layer.h \
           imagelayer.h \
           util.h \
           viewport.h \
           box2ddebugdrawitem.h \
           enums.h \
           behavior.h \
           scriptbehavior.h \
           box2dcontact.h \
           box2dcontactlistener.h \
           fill.h \
           colorfill.h \
           shape.h \
           rectangle.h \
           triangle.h \
           polygon.h \
           polyline.h \
           circle.h \
           line.h \
           fixture.h \
           material.h

SOURCES += entity.cpp \
           scene.cpp \
           game.cpp \
           plugins.cpp \
           spritesheet.cpp \
           sprite.cpp \
           spriteanimation.cpp \
           animationtransition.cpp \
           box2djointitem.cpp \
           box2dbaseitem.cpp \
           box2ddistancejointitem.cpp \
           box2dmousejointitem.cpp \
           layer.cpp \
           imagelayer.cpp \
           util.cpp \
           viewport.cpp \
           box2ddebugdrawitem.cpp \
           behavior.cpp \
           scriptbehavior.cpp \
           box2dcontact.cpp \
           box2dcontactlistener.cpp \
           fill.cpp \
           colorfill.cpp \
           shape.cpp \
           rectangle.cpp \
           circle.cpp \
           line.cpp \
           triangle.cpp \
           polygon.cpp \
           polyline.cpp \
           fixture.cpp \
           material.cpp

QMAKE_POST_LINK = $$QMAKE_COPY $$PWD/qmldir $$OUT_PWD/imports/QuasiGame

!isEmpty(QTPATH): target.path = $$QTPATH/imports/$$TARGETPATH
else: target.path = $$[QT_INSTALL_IMPORTS]/$$TARGETPATH

qmlpluginfiles.path = $$target.path
qmlpluginfiles.files += \
    $$PWD/qmldir \
    $$OUT_PWD/imports/QuasiGame/*

INSTALLS += target qmlpluginfiles
