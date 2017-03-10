project( gpgmepp )
#KDE4_NO_ENABLE_FINAL(gpgmepp)
if (MINGW)
  set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -mms-bitfields")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mms-bitfields")
endif()

include_directories(  ${GPGME_INCLUDES} ${Boost_INCLUDE_DIR} )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${KDE4_ENABLE_EXCEPTIONS}")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config-gpgme++.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-gpgme++.h )

## gpgme comes in these flavours on each of the platforms:
##  Windows: gpgme, gpgme-glib
##     Unix: gpgme
## We're building corresponding gpgme++ flavours

set(gpgme_LIB_SRCS
        exception.cpp
        context.cpp key.cpp
        trustitem.cpp
        data.cpp
        callbacks.cpp
        eventloopinteractor.cpp
        editinteractor.cpp
        assuanresult.cpp
        keylistresult.cpp
        keygenerationresult.cpp
        importresult.cpp
        decryptionresult.cpp
        verificationresult.cpp
        signingresult.cpp
        encryptionresult.cpp
        engineinfo.cpp
        gpgsetexpirytimeeditinteractor.cpp
        gpgsetownertrusteditinteractor.cpp
        gpgsignkeyeditinteractor.cpp
        gpgadduserideditinteractor.cpp
        defaultassuantransaction.cpp
        scdgetinfoassuantransaction.cpp
        gpgagentgetinfoassuantransaction.cpp
        vfsmountresult.cpp
        configuration.cpp
)

set( _gpgmepp_version 2.8.0 )
set( _gpgmepp_soversion 2 )

set( GPGMEPP_INCLUDE ${INCLUDE_INSTALL_DIR} ${GPGME_INCLUDES} ${Boost_INCLUDE_DIR} )

if ( GPGME_VANILLA_FOUND )
   add_library( gpgmepp ${LIBRARY_TYPE} ${gpgme_LIB_SRCS} context_vanilla.cpp )
   generate_export_header(gpgmepp EXPORT_FILE_NAME gpgme++_export.h)

   target_link_libraries( gpgmepp LINK_PRIVATE ${GPGME_VANILLA_LIBRARIES} )
   set_target_properties( gpgmepp PROPERTIES
                                  VERSION     ${_gpgmepp_version}
                                  SOVERSION   ${_gpgmepp_soversion}
                                  OUTPUT_NAME gpgme++
   )
   set(GPGMEPP_VANILLA_LIBRARY ${LIBRARY_OUTPUT_PATH}/libgpgmepp.so)
   install(TARGETS gpgmepp EXPORT kdepimlibsLibraryTargets ${INSTALL_TARGETS_DEFAULT_ARGS} COMPONENT Devel)

endif()

if ( GPGME_GLIB_FOUND )
   add_library( gpgmepp-glib ${LIBRARY_TYPE} ${gpgme_LIB_SRCS} context_glib.cpp )
   target_link_libraries( gpgmepp-glib LINK_PRIVATE ${GPGME_GLIB_LIBRARIES} )
   set_target_properties( gpgmepp-glib PROPERTIES
                                       VERSION     ${_gpgmepp_version}
                                       SOVERSION   ${_gpgmepp_soversion}
                                       OUTPUT_NAME gpgme++-glib DEFINE_SYMBOL gpgmepp_EXPORTS
   )
   set(GPGMEPP_GLIB_LIBRARY ${LIBRARY_OUTPUT_PATH}/libgpgmepp.so)
   install(TARGETS gpgmepp-glib EXPORT kdepimlibsLibraryTargets ${INSTALL_TARGETS_DEFAULT_ARGS} )
endif()


########### install files ###############

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/GpgmeppConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/GpgmeppConfig.cmake @ONLY )

if ( GPGME_FOUND )

   add_subdirectory( interfaces )

   install(FILES
        global.h error.h exception.h context.h key.h trustitem.h
        eventloopinteractor.h editinteractor.h data.h gpgmefw.h result.h
        assuanresult.h
        keylistresult.h keygenerationresult.h
        importresult.h decryptionresult.h verificationresult.h
        signingresult.h encryptionresult.h notation.h engineinfo.h
        gpgsetexpirytimeeditinteractor.h
        gpgsetownertrusteditinteractor.h
        gpgsignkeyeditinteractor.h
        gpgadduserideditinteractor.h
        defaultassuantransaction.h
        scdgetinfoassuantransaction.h
        gpgagentgetinfoassuantransaction.h
        configuration.h
        ${CMAKE_CURRENT_BINARY_DIR}/gpgme++_export.h vfsmountresult.h
        DESTINATION ${INCLUDE_INSTALL_DIR}/gpgme++ COMPONENT Devel
   )

   install(
     FILES
     ${CMAKE_CURRENT_BINARY_DIR}/GpgmeppConfig.cmake
     DESTINATION
     ${LIB_INSTALL_DIR}/gpgmepp )

endif()
