TEMPLATE = app
TARGET = tst_matomo

QT       += testlib
CONFIG   += testcase

include( ../../../src/plugin/plugin.pri )

SOURCES += \
    tst_matomo.cpp
