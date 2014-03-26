TEMPLATE = lib
CONFIG += qt plugin

QT += quick

TARGET = quasigameplugin
TARGETPATH = QuasiGame

API_VER=1.0
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
           box2djoint.h \
           box2dbase.h \
           box2ddistancejoint.h \
           box2dmousejoint.h \
           layer.h \
           imagelayer.h \
           util.h \
           box2ddebugdraw.h \
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
           box2djoint.cpp \
           box2dbase.cpp \
           box2ddistancejoint.cpp \
           box2dmousejoint.cpp \
           layer.cpp \
           imagelayer.cpp \
           util.cpp \
           box2ddebugdraw.cpp \
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
else: target.path = $$[QT_INSTALL_QML]/$$replace(TARGETPATH, \\., /).$$API_VER

qmlpluginfiles.path = $$target.path
qmlpluginfiles.files += \
    $$PWD/qmldir \
    $$OUT_PWD/imports/QuasiGame/*

INSTALLS += target qmlpluginfiles
