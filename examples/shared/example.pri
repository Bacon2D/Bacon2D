TEMPLATE = app

QT += gui qml quick

SOURCES += $$PWD/main.cpp

include(deployment.pri)

EXAMPLE_QML_FILES += \
    main.qml

# obeezzy: Add TMX files
OTHER_FILES += \
    $$EXAMPLE_QML_FILES \
    $$EXAMPLE_IMAGE_FILES \
    $$EXAMPLE_SOUND_FILES \
    $$EXAMPLE_TMX_FILES

# Create the resource file
GENERATED_RESOURCE_FILE = $$OUT_PWD/resources.qrc

# obeezzy: Add TMX files
INCLUDED_RESOURCE_FILES = \
    $$EXAMPLE_QML_FILES \
    $$EXAMPLE_IMAGE_FILES \
    $$EXAMPLE_SOUND_FILES \
    $$EXAMPLE_TMX_FILES

RESOURCE_CONTENT = \
    "<RCC>" \
    "<qresource prefix=\"/\">"

win32 {
    for(resourcefile, INCLUDED_RESOURCE_FILES) {
        resourcefileabsolutepath = $$absolute_path($$resourcefile, $$_PRO_FILE_PWD_)
        RESOURCE_CONTENT += "<file alias=\"$$resourcefile\">$$resourcefileabsolutepath</file>"
    }
}
unix {
    for(resourcefile, INCLUDED_RESOURCE_FILES) {
        resourcefileabsolutepath = $$shell_path($$absolute_path($$resourcefile, $$_PRO_FILE_PWD_))
        RESOURCE_CONTENT += "<file alias=\"$$resourcefile\">$$resourcefileabsolutepath</file>"
    }
}

RESOURCE_CONTENT += \
    "</qresource>" \
    "</RCC>"

write_file($$GENERATED_RESOURCE_FILE, RESOURCE_CONTENT)|error("Aborting.")

RESOURCES += $$GENERATED_RESOURCE_FILE
