#-------------------------------------------------
#
# Project created by QtCreator 2014-11-19T00:29:37
#
#-------------------------------------------------

QT       += qml quick testlib

QT       -= gui

TARGET = tst_bacon2d
CONFIG   += warn_on qmltestcase

TEMPLATE = app
IMPORTPATH += $$OUT_PWD/../src/qml
SOURCES += \
    tst_bacon2d.cpp
OTHER_FILES += \
    tst_physics.qml \
    tst_scene.qml
