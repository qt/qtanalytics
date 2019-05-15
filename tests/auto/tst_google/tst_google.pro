TEMPLATE = app
TARGET = tst_google

QT       += testlib
CONFIG   += testcase

include( ../../../src/plugin/plugin.pri )

SOURCES += \
    tst_google.cpp
