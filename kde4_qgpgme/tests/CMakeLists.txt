if ( GPGME_VANILLA_FOUND )
   set( _kde4_qgpgme_libgpgme kde4_gpgmepp )
endif()

set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )
include_directories( ${GPGME_INCLUDES} )
include_directories( ${Boost_INCLUDE_DIR} )
link_directories( ${_gpgme_library_dirs} )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${KDE4_ENABLE_EXCEPTIONS}")

########### next target ###############

set( kde4_qgpgme_TESTS
  dataprovidertest
  installtest
  # PORT ME AWAY FROM EVENT LOOPS
  #gpgsetexpirytimetest
  #gpgsetownertrusttest
  #gpgsignkeytest
  #gpgadduseridtest
  )

foreach( _kde4_qgpgme_test ${kde4_qgpgme_TESTS} )
  kde4_add_executable( "${_kde4_qgpgme_test}" TEST "${_kde4_qgpgme_test}.cpp" )
  if (WIN32) # what's up?
    target_link_libraries( "${_kde4_qgpgme_test}" kde4_qgpgme ${_kde4_qgpgme_libgpgme} ${_gpgme_vanilla_library} ${_gpg_error_library} ${QT_QTCORE_LIBRARY} )
  else()
    target_link_libraries( "${_kde4_qgpgme_test}" kde4_qgpgme ${_kde4_qgpgme_libgpgme} gpgme gpg-error ${QT_QTCORE_LIBRARY} )
  endif()
endforeach( _kde4_qgpgme_test )

########### next target ###############

# PORT ME AWAY FROM EVENT LOOPS
#kde4_add_executable(editinteractortest TEST editinteractortest.cpp)
#target_link_libraries(editinteractortest  kde4_qgpgme ${QT_QTGUI_LIBRARY})
