include(doc/doc.pri)

TEMPLATE = subdirs

SUBDIRS += src \
    tests

PROJECT_NAME = bacon2d
PROJECT_VERSION = 0.90.3

DISTNAME = $${PROJECT_NAME}-$${PROJECT_VERSION}
dist.commands = "./git-archive-all.sh --prefix $${DISTNAME}/ $${DISTNAME}.tar && bzip2 $${DISTNAME}.tar"
QMAKE_EXTRA_TARGETS += dist
