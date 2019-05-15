TEMPLATE = lib
TARGET = analytics
CONFIG += plugin

TARGET = $$qtLibraryTarget($$TARGET)
uri = analytics

include ( ../../qtanalytics.pri )
include ( ../../doc/doc.pri )
include ( plugin.pri )
# Input
SOURCES += \
    plugin.cpp

HEADERS += \
    plugin.h

DISTFILES = qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir

installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
defined(ANALYTICS_DIR, var) {
    installPath = $${ANALYTICS_DIR}/analytics
    message( "The plugin will be installed in "$${ANALYTICS_DIR}/analytics )
}

qmldir.path = $$installPath
target.path = $$installPath
INSTALLS += target qmldir

OBJECTS_DIR = .obj
MOC_DIR = .moc

