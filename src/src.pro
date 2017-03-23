TEMPLATE = lib
CONFIG += qt plugin

QMAKE_HOST_ARCH=$$QMAKE_HOST.arch
  !equals(QMAKE_HOST_ARCH, $$QT_ARCH) {
     CONFIG += cross_build
}

CONFIG += c++11

QT += quick

TARGET = bacon2dplugin
TARGETPATH = Bacon2D

API_VER=1.0
DESTDIR = $$OUT_PWD/qml/Bacon2D

OBJECTS_DIR = tmp
MOC_DIR = tmp

DEPENDPATH += .
INCLUDEPATH += .
INCLUDEPATH += ../3rdparty/qml-box2d/
INCLUDEPATH += ../3rdparty/tiled/src/

DEFINES += STATIC_PLUGIN_BOX2D
include(../3rdparty/qml-box2d/box2d-static.pri)


include(../3rdparty/tiled/src/libtiled/libtiled-static.pri)
include($$PWD/tmx/tmx.pri)

win32:DEFINES += WIN32

HEADERS += entity.h \
           enums.h \
           scene.h \
           game.h \
           plugins.h \
           spritesheet.h \
           sprite.h \
           spriteanimation.h \
           animationtransition.h \
           animationchangeevent.h \
           bacon2dlayer.h \
           bacon2dimagelayer.h \
           viewport.h \
           behavior.h \
           scriptbehavior.h \
           scrollbehavior.h \
           scrollbehaviorimpl.h \
           imagelayerscrollbehavior.h \
           layerscrollbehavior.h \
           settings.h \
           tiledobject.h \
           tiledlayer.h \
           tiledscene.h \

SOURCES += entity.cpp \
           enums.cpp \
           scene.cpp \
           game.cpp \
           plugins.cpp \
           spritesheet.cpp \
           sprite.cpp \
           spriteanimation.cpp \
           animationtransition.cpp \
           bacon2dlayer.cpp \
           bacon2dimagelayer.cpp \
           viewport.cpp \
           behavior.cpp \
           scriptbehavior.cpp \
           scrollbehavior.cpp \
           imagelayerscrollbehavior.cpp \
           layerscrollbehavior.cpp \
           settings.cpp \
           tiledscene.cpp \
           tiledlayer.cpp \
           tiledobject.cpp

!isEmpty(QTPATH): target.path = $$QTPATH/qml/$$TARGETPATH
else: target.path = $$[QT_INSTALL_QML]/$$replace(TARGETPATH, \\., /).$$API_VER
;

QMLFILES += \
            $$PWD/InfiniteScrollEntity.qml \
            $$PWD/PhysicsEntity.qml \
            $$PWD/BoxBody.qml \
            $$PWD/ChainBody.qml \
            $$PWD/CircleBody.qml \
            $$PWD/EdgeBody.qml \
            $$PWD/ImageBoxBody.qml \
            $$PWD/PolygonBody.qml \
            $$PWD/Boundaries.qml \
            $$PWD/RectangleBoxBody.qml \
            $$PWD/qmldir

# Copy qml files post build
win32 {
    DESTDIR ~= s,/,\\,g
    QMLFILES ~= s,/,\\,g
    for(FILE, QMLFILES){
        QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$FILE) $$quote($$DESTDIR) $$escape_expand(\\n\\t)
    }
    QMAKE_POST_LINK += $$[QT_INSTALL_BINS]/qmlplugindump -noinstantiate -notrelocatable Bacon2D $$API_VER $$OUT_PWD/qml  > $$DESTDIR\plugins.qmltypes
}
unix {
    QMAKE_POST_LINK += $$QMAKE_COPY $$QMLFILES $$DESTDIR $$escape_expand(\\n\\t)
    !cross_build {
        QMAKE_POST_LINK += $$[QT_INSTALL_BINS]/qmlplugindump -noinstantiate -notrelocatable Bacon2D $$API_VER $$OUT_PWD/qml  > $$DESTDIR/plugins.qmltypes
    }
}

qmltypes.path = $$target.path
qmltypes.files += $$DESTDIR/plugins.qmltypes
export(qmltypes.files)

qmlpluginfiles.path = $$target.path
qmlpluginfiles.files = $$QMLFILES

QMAKE_EXTRA_TARGETS += qmltypes qmlpluginfiles
INSTALLS += target qmltypes qmlpluginfiles
