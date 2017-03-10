# - Try to find the KDE4_QGpgME library
# Once done this will define
#
# KDE4_QGPGME_FOUND
# KDE4_QGPGME_LIBRARIES
# KDE4_QGPGME_INCLUDE_DIR

# What we do here is a bit simplictic, but it's no worse than what
# people were using in kdepim up to now...

find_package(Gpgme QUIET)

if(GPGME_FOUND)

   find_library(_KDE4_QGPGME_EXTRA_LIBRARY kde4_gpgme++
                HINTS ${GPGME_LIBRARY_DIR})

   find_library(KDE4_QGPGME_LIBRARY kde4_qgpgme
                HINTS ${GPGME_LIBRARY_DIR})

   if (KDE4_QGPGME_LIBRARY)
      # get the libdirectory and then go one up
      get_filename_component(_KDE4_QGPGME_PREFIX "${KDE4_QGPGME_LIBRARY}" PATH)
      get_filename_component(_KDE4_QGPGME_PREFIX "${_KDE4_QGPGME_PREFIX}" PATH)
      find_path(KDE4_QGPGME_INCLUDE_DIR kde4_qgpgme/qgpgme_export.h
                HINTS "${_KDE4_QGPGME_PREFIX}/include" )
   endif()

   set(KDE4_QGPGME_LIBRARIES ${KDE4_QGPGME_LIBRARY} ${_KDE4_QGPGME_EXTRA_LIBRARY} ${GPGME_VANILLA_LIBRARIES})

endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(KDE4_QGpgme  DEFAULT_MSG  KDE4_QGPGME_LIBRARY KDE4_QGPGME_INCLUDE_DIR _KDE4_QGPGME_EXTRA_LIBRARY)

mark_as_advanced(KDE4_QGPGME_LIBRARY _KDE4_QGPGME_EXTRA_LIBRARY KDE4_QGPGME_INCLUDE_DIR)
