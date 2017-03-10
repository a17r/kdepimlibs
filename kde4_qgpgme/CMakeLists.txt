
set( _any_gpgme_found false )

set( _kde4_qgpgme_version 1.0.1 )
set( _kde4_qgpgme_soversion 1 )

if ( WIN32 AND GPGME_VANILLA_FOUND )

   # on Windows, we require gpgme(-vanilla), which is thread-safe

   set( _any_gpgme_found true )
   set( _kde4_qgpgme_libgpgme kde4_gpgmepp )
   #set( _kde4_qgpgme_extra_src eventloopinteractor_win.cpp )

endif()

if ( NOT WIN32 AND GPGME_VANILLA_FOUND )

   # on Unix, we require gpgme(-vanilla), which is thread-safe

   set( _any_gpgme_found true )
   set( _kde4_qgpgme_libgpgme kde4_gpgmepp )
   set( _kde4_qgpgme_extra_src eventloopinteractor.cpp eventloopinteractor_unix.cpp )
   set( _kde4_qgpgme_extra_headers eventloopinteractor.h )

endif()

# build / install only if any useable gpgme was found:

if ( _any_gpgme_found )

   include_directories( ${CMAKE_CURRENT_BINARY_DIR} ${GPGME_INCLUDES} ${CMAKE_SOURCE_DIR}/gpgme++ ${Boost_INCLUDE_DIR} )

   add_subdirectory( tests )

   set( kde4_qgpgme_LIB_SRCS
        dataprovider.cpp
        ${_kde4_qgpgme_extra_src}
   )

   add_library( kde4_qgpgme ${LIBRARY_TYPE} ${kde4_qgpgme_LIB_SRCS} )
   generate_export_header(kde4_qgpgme BASE_NAME qgpgme)

   target_link_libraries( kde4_qgpgme LINK_PRIVATE ${QT_QTCORE_LIBRARY} ${_kde4_qgpgme_libgpgme} )

   set_target_properties( kde4_qgpgme PROPERTIES
     VERSION ${_kde4_qgpgme_version}
     SOVERSION ${_kde4_qgpgme_soversion}
   )

   install( TARGETS kde4_qgpgme EXPORT kdepimlibsLibraryTargets ${INSTALL_TARGETS_DEFAULT_ARGS})

   install( FILES
     ${CMAKE_CURRENT_BINARY_DIR}/qgpgme_export.h
     ${_kde4_qgpgme_extra_headers}
     dataprovider.h 
     DESTINATION ${INCLUDE_INSTALL_DIR}/kde4_qgpgme COMPONENT Devel )

endif()
