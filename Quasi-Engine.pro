TEMPLATE = subdirs

SUBDIRS += src

contains(BUILD_EXAMPLES, 1) {
    SUBDIRS += examples demos
}
