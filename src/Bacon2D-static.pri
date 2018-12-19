# Include this file in your .pro file to statically compile the Bacon2D QML
# plugin into your project.
#
# Basic usage instructions:
#
#  #include <plugins.h>
#
#  int main(int argc, char *argv[])
#  {
#      QApplication app(argc, argv);
#
#      Plugin plugin;
#      plugin.registerTypes("Bacon2D");
#
#      ...
#  }

INCLUDEPATH += $$PWD

DEPENDPATH += .
INCLUDEPATH += $$PWD/../3rdparty/qml-box2d/
INCLUDEPATH += $$PWD/../3rdparty/tiled/src/

DEFINES += STATIC_PLUGIN_BOX2D
include($$PWD/../3rdparty/qml-box2d/box2d-static.pri)
include($$PWD/../3rdparty/tiled/src/libtiled/libtiled-static.pri)
include($$PWD/tmx/tmx.pri)

RESOURCES += \
	$$PWD/bacon2d-static.qrc

HEADERS += \
	$$PWD/entity.h \
	$$PWD/enums.h \
	$$PWD/scene.h \
	$$PWD/game.h \
	$$PWD/plugins.h \
	$$PWD/spritesheet.h \
	$$PWD/sprite.h \
	$$PWD/spriteanimation.h \
	$$PWD/animationtransition.h \
	$$PWD/animationchangeevent.h \
	$$PWD/bacon2dlayer.h \
	$$PWD/bacon2dimagelayer.h \
	$$PWD/viewport.h \
	$$PWD/behavior.h \
	$$PWD/scriptbehavior.h \
	$$PWD/scrollbehavior.h \
	$$PWD/scrollbehaviorimpl.h \
	$$PWD/imagelayerscrollbehavior.h \
	$$PWD/layerscrollbehavior.h \
	$$PWD/settings.h \
	$$PWD/tiledobject.h \
	$$PWD/tiledlayer.h \
	$$PWD/tiledscene.h \

SOURCES += \
	$$PWD/entity.cpp \
	$$PWD/enums.cpp \
	$$PWD/scene.cpp \
	$$PWD/game.cpp \
	$$PWD/plugins.cpp \
	$$PWD/spritesheet.cpp \
	$$PWD/sprite.cpp \
	$$PWD/spriteanimation.cpp \
	$$PWD/animationtransition.cpp \
	$$PWD/bacon2dlayer.cpp \
	$$PWD/bacon2dimagelayer.cpp \
	$$PWD/viewport.cpp \
	$$PWD/behavior.cpp \
	$$PWD/scriptbehavior.cpp \
	$$PWD/scrollbehavior.cpp \
	$$PWD/imagelayerscrollbehavior.cpp \
	$$PWD/layerscrollbehavior.cpp \
	$$PWD/settings.cpp \
	$$PWD/tiledscene.cpp \
	$$PWD/tiledlayer.cpp \
	$$PWD/tiledobject.cpp
