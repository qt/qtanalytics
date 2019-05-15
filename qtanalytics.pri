isEmpty(PREFIX): PREFIX = $$[QT_INSTALL_PREFIX]
isEmpty(EXAMPLES_PREFIX): EXAMPLES_PREFIX = $$[QT_INSTALL_EXAMPLES]/qtanalytics

VERSIONS = $$split(VERSION, ".")
VERSION_MAJOR = $$member(VERSIONS, 0)
unset(VERSIONS)

DEFINES += QTANALYTICS_VERSION=$$VERSION
!isEmpty(QTANALYTICS_VERSION_EXTRA): DEFINES += QTANALYTICS_VERSION_EXTRA="\"$$QTANALYTICS_VERSION_EXTRA\""
!isEmpty(QTANALYTICS_REVISION): DEFINES += QTANALYTICS_REVISION=$$QTANALYTICS_REVISION
!isEmpty(QTANALYTICS_SETTINGS_VARIANT): DEFINES += QTANALYTICS_SETTINGS_VARIANT=$$QTANALYTICS_SETTINGS_VARIANT

# from qtcreator.pri
defineTest(minQtVersion) {
    maj = $$1
    min = $$2
    patch = $$3
    isEqual(QT_MAJOR_VERSION, $$maj) {
        isEqual(QT_MINOR_VERSION, $$min) {
            isEqual(QT_PATCH_VERSION, $$patch) {
                return(true)
            }
            greaterThan(QT_PATCH_VERSION, $$patch) {
                return(true)
            }
        }
        greaterThan(QT_MINOR_VERSION, $$min) {
            return(true)
        }
    }
    greaterThan(QT_MAJOR_VERSION, $$maj) {
        return(true)
    }
    return(false)
}
