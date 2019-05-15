TEMPLATE = app
TARGET = tst_config

QT       += testlib
CONFIG   += testcase

include( ../../../src/plugin/plugin.pri )

SOURCES += \
    tst_config.cpp

RESOURCES += \
    tst_config.qrc
