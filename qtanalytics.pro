TEMPLATE = subdirs

SUBDIRS += \
    src \
    examples \
    tests \
    doc

examples.depends += src
tests.depends = src

OTHER_FILES += \
    README.md \
    .qmake.conf


include(doc/doc.pri)
