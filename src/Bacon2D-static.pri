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
INCLUDEPATH += ../3rdparty/qml-box2d/

DEFINES += STATIC_PLUGIN_BOX2D
include(../3rdparty/qml-box2d/box2d-static.pri)

HEADERS += \
        $$PWD/animationchangeevent.h \
        $$PWD/animationtransition.h \
        $$PWD/behavior.h \
        $$PWD/entity.h \
        $$PWD/enums.h \
        $$PWD/game.h \
        $$PWD/imagelayer.h \
        $$PWD/imagelayerscrollbehavior.h \
        $$PWD/layer.h \
        $$PWD/layerscrollbehavior.h \
        $$PWD/plugins.h \
        $$PWD/scene.h \
        $$PWD/scriptbehavior.h \
        $$PWD/scrollbehavior.h \
        $$PWD/scrollbehaviorimpl.h \
        $$PWD/spriteanimation.h \
        $$PWD/sprite.h \
        $$PWD/spritesheet.h \
        $$PWD/viewport.h \
        $$PWD/settings.h 

SOURCES += \
        $$PWD/animationtransition.cpp \
        $$PWD/behavior.cpp \
        $$PWD/entity.cpp \
        $$PWD/enums.cpp \
        $$PWD/game.cpp \
        $$PWD/imagelayer.cpp \
        $$PWD/imagelayerscrollbehavior.cpp \
        $$PWD/layer.cpp \
        $$PWD/layerscrollbehavior.cpp \
        $$PWD/plugins.cpp \
        $$PWD/scene.cpp \
        $$PWD/scriptbehavior.cpp \
        $$PWD/scrollbehavior.cpp \
        $$PWD/spriteanimation.cpp \
        $$PWD/sprite.cpp \
        $$PWD/spritesheet.cpp \
        $$PWD/viewport.cpp \
        $$PWD/settings.cpp
