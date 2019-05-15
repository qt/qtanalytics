QT += qml quick
CONFIG += c++11

SOURCES += \
    $$PWD/analytics.cpp \
    $$PWD/configutil.cpp \
    $$PWD/context.cpp \
    $$PWD/googlebuilder.cpp \
    $$PWD/hitbuilder.cpp \
    $$PWD/matomobuilder.cpp

HEADERS += \
    $$PWD/analytics.h \
    $$PWD/configutil.h \
    $$PWD/context.h \
    $$PWD/googlebuilder.h \
    $$PWD/hitbuilder.h \
    $$PWD/matomobuilder.h

INCLUDEPATH = $$PWD
