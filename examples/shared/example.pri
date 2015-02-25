TEMPLATE = app

QT += gui qml quick

SOURCES += $$PWD/main.cpp

include(deployment.pri)

EXAMPLE_QML_FILES += \
    main.qml

OTHER_FILES += \
    $$EXAMPLE_QML_FILES \
    $$EXAMPLE_IMAGE_FILES \
    $$EXAMPLE_SOUND_FILES

# Create the resource file
GENERATED_RESOURCE_FILE = $$OUT_PWD/resources.qrc

INCLUDED_RESOURCE_FILES = \
    $$EXAMPLE_QML_FILES \
    $$EXAMPLE_IMAGE_FILES \
    $$EXAMPLE_SOUND_FILES

RESOURCE_CONTENT = \
    "<RCC>" \
    "<qresource prefix=\"/\">"

for(resourcefile, INCLUDED_RESOURCE_FILES) {
    resourcefileabsolutepath = $$shell_path($$absolute_path($$resourcefile, $$_PRO_FILE_PWD_))
    RESOURCE_CONTENT += "<file alias=\"$$resourcefile\">$$resourcefileabsolutepath</file>"
}

RESOURCE_CONTENT += \
    "</qresource>" \
    "</RCC>"

write_file($$GENERATED_RESOURCE_FILE, RESOURCE_CONTENT)|error("Aborting.")

RESOURCES += $$GENERATED_RESOURCE_FILE
