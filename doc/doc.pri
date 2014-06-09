QDOC = QT_INSTALL_DOCS=$$[QT_INSTALL_DOCS] $$[QT_INSTALL_BINS]/qdoc

QT_INSTALL_DOCS = /usr/share/qt5/doc/global/

QMAKE_EXTRA_TARGETS += docs clean-docs docs-html clean-docs-html

docs-html.commands = \
        "$${QDOC} $${PWD}/bacon2d.qdocconf"

docs.files = $$PWD/html
docs.path = $${INSTALL_PREFIX}/share/bacon2d/doc
docs.depends = docs-html

INSTALLS += docs

clean-docs-html.commands = \
    "rm -rf $${PWD}/html"

clean-docs.depends = clean-docs-html
