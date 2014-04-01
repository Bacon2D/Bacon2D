include(doc/doc.pri)
TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += src

contains(BUILD_EXAMPLES, 1) {
    SUBDIRS += examples demos
}
