TARGET = z            # The name of the output library - can be whatever you want
TEMPLATE = lib        # Tells Qt that we are compiling a library so the output will be bundled into a .a or .so file
CONFIG += staticlib   # Tells Qt that we want a static library, so a .a file. Remove this and you will get a .so file

QMAKE_CFLAGS_WARN_ON -= -Wall   # Optional - disable warnings when compiling this library
QMAKE_CXXFLAGS_WARN_ON -= -Wall # Optional - disable warnings when compiling this library

HEADERS += \
    crc32.h \
    deflate.h \
    gzguts.h \
    inffast.h \
    inffixed.h \
    inflate.h \
    inftrees.h \
    trees.h \
    zconf.h \
    zlib.h \
    zutil.h

SOURCES += \
    adler32.c \
    compress.c \
    crc32.c \
    deflate.c \
    gzclose.c \
    gzlib.c \
    gzread.c \
    gzwrite.c \
    infback.c \
    inffast.c \
    inflate.c \
    inftrees.c \
    trees.c \
    uncompr.c \
    zutil.c
