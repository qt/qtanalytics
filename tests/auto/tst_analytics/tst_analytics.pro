TEMPLATE = app
TARGET = tst_analytics

QT       += testlib
CONFIG   += testcase

include( ../../../src/plugin/plugin.pri )

SOURCES += \
    tst_analytics.cpp
