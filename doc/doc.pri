build_online_docs: {
    QMAKE_DOCS_TARGETDIR = qtanalytics
    QMAKE_DOCS = $$PWD/qtanalytics-online.qdocconf
} else {
    QMAKE_DOCS = $$PWD/qtanalytics.qdocconf
}

load(qt_docs_targets)

OTHER_FILES += \
    $$PWD/*.qdocconf \
    $$PWD/*.qdoc \
    $$PWD/examples/*.qdoc \
    $$PWD/images/*.png
