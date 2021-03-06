cmake_minimum_required(VERSION 2.8.12)

project(Akonadi-Mime)

# ECM setup
set(KF5_VERSION "5.22.0")
find_package(ECM ${KF5_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
set(QT_REQUIRED_VERSION "5.6.0")
include(GenerateExportHeader)
include(ECMGenerateHeaders)
include(ECMGeneratePriFile)
include(ECMPackageConfigHelpers)
include(ECMSetupVersion)
include(FeatureSummary)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(ECMQtDeclareLoggingCategory)

set(KDEPIMLIBS_VERSION "5.2.40")
set(AKONADI_VERSION "5.2.40")
set(KF5_MIME_VERSION "5.2.40")

ecm_setup_version(${KDEPIMLIBS_VERSION} VARIABLE_PREFIX AKONADIMIME
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/akonadi-mime_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5AkonadiMimeConfigVersion.cmake"
                        SOVERSION 5
)

########### Find packages ###########
find_package(KF5DBusAddons ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5KIO ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5Config ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5I18n ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5XmlGui ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5Mime ${KF5_MIME_VERSION} CONFIG REQUIRED)
find_package(KF5ItemModels ${KF5_MIME_VERSION} CONFIG REQUIRED)

find_package(KF5Akonadi ${AKONADI_VERSION} CONFIG REQUIRED)

set( SHARED_MIME_INFO_MINIMUM_VERSION "0.40" )
find_package( SharedMimeInfo REQUIRED )

find_package(LibXslt)
set_package_properties(LibXslt PROPERTIES
    DESCRIPTION "xsltproc"
    URL "http://xmlsoft.org/XSLT/"
    TYPE REQUIRED
    PURPOSE "Needed to generate D-Bus interface specifications"
)

########### Targets ###########

add_definitions(-DTRANSLATION_DOMAIN=\"libakonadi-kmime5\")
add_definitions("-DQT_NO_CAST_FROM_ASCII -DQT_NO_CAST_TO_ASCII")

add_subdirectory(src)

if(BUILD_TESTING)
    add_subdirectory(autotests)
    add_subdirectory(tests)
endif()

########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5AkonadiMime")

ecm_configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/KF5AkonadiMimeConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/KF5AkonadiMimeConfig.cmake"
  INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/KF5AkonadiMimeConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/KF5AkonadiMimeConfigVersion.cmake"
  DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
  COMPONENT Devel
)

install(EXPORT KF5AkonadiMimeTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF5AkonadiMimeTargets.cmake NAMESPACE KF5::)

install(FILES
   ${CMAKE_CURRENT_BINARY_DIR}/akonadi-mime_version.h
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5} COMPONENT Devel
)

if ("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")
  feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
endif()
