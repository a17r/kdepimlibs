set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${KDE4_ENABLE_EXCEPTIONS}")

include_directories(
  ${Boost_INCLUDE_DIR}
  ${CMAKE_BINARY_DIR}/kmime
)

if (NOT KDEPIM_NO_AKONADI)
include_directories(
  ${CMAKE_BINARY_DIR}/akonadi
  ${CMAKE_BINARY_DIR}/akonadi/kmime
)
endif()

option(MAILTRANSPORT_INPROCESS_SMTP "false" "Use in-process SMTP instead of KIO slaves (note that this changes the mailtransport license from LGPL to GPL!)")

add_subdirectory(kconf_update)
add_subdirectory(tests)

add_definitions("-DQT_NO_CAST_FROM_ASCII -DQT_NO_CAST_TO_ASCII")
add_definitions(-DKDE_DEFAULT_DEBUG_AREA=5324)
add_definitions(-DUSES_DEPRECATED_MAILTRANSPORT_API) # for transportmanager
add_definitions(
  -DMAILTRANSPORT_DEPRECATED=
)
# This one won't be needed when CMake 2.8.13 is depended on.
add_definitions(
  -DMAILTRANSPORT_DEPRECATED_EXPORT=MAILTRANSPORT_EXPORT
)

if (NOT KDEPIM_NO_AKONADI)
  add_definitions("-DMAILTRANSPORT_AKONADI_SUPPORT")
endif()

if(MAILTRANSPORT_INPROCESS_SMTP)
  add_definitions("-DMAILTRANSPORT_INPROCESS_SMTP")
  include_directories(${SASL2_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/kioslave)
  set(mailtransport_lib_srcs
    ../kioslave/smtp/command.cpp
    ../kioslave/smtp/capabilities.cpp
    ../kioslave/smtp/request.cpp
    ../kioslave/smtp/response.cpp
    ../kioslave/smtp/transactionstate.cpp
    ../kioslave/smtp/smtpsessioninterface.cpp
    smtp/smtpsession.cpp
  )
endif()

set(mailtransport_lib_srcs
  ${mailtransport_lib_srcs}
  transport.cpp
  transportmanager.cpp
  transporttype.cpp

  transportcombobox.cpp
  transportconfigwidget.cpp

  transportjob.cpp
  sendmailjob.cpp
  smtpjob.cpp
  precommandjob.cpp

  legacydecrypt.cpp
  socket.cpp
  servertest.cpp

  transportconfigdialog.cpp
  sendmailconfigwidget.cpp
  smtpconfigwidget.cpp

  transportlistview.cpp
  transportmanagementwidget.cpp
  addtransportdialog.cpp
)

if (NOT KDEPIM_NO_AKONADI)
set(mailtransport_lib_srcs
  ${mailtransport_lib_srcs}

  filteractionjob.cpp
  resourcesendjob.cpp

  dispatcherinterface.cpp
  messagequeuejob.cpp
  outboxactions.cpp

  attributeregistrar.cpp
  dispatchmodeattribute.cpp
  errorattribute.cpp
  sentactionattribute.cpp
  sentbehaviourattribute.cpp
  transportattribute.cpp
)
endif()

kde4_add_ui_files(mailtransport_lib_srcs
  sendmailsettings.ui
  addtransportdialog.ui
  transportmanagementwidget.ui
)
if(KDEPIM_MOBILE_UI)
  kde4_add_ui_files(mailtransport_lib_srcs smtpsettings_mobile.ui)
else()
  kde4_add_ui_files(mailtransport_lib_srcs smtpsettings_desktop.ui)
endif()

kde4_add_kcfg_files(mailtransport_lib_srcs transportbase.kcfgc)

add_library(mailtransport ${LIBRARY_TYPE} ${mailtransport_lib_srcs})
generate_export_header(mailtransport)
target_link_libraries(mailtransport LINK_PRIVATE ${KDE4_KIO_LIBS})
if (NOT KDEPIM_NO_AKONADI)
target_link_libraries(mailtransport LINK_PRIVATE akonadi-kde akonadi-kmime kmime)
endif()
if(MAILTRANSPORT_INPROCESS_SMTP)
  target_link_libraries(mailtransport LINK_PRIVATE ${SASL2_LIBRARIES} kpimutils)
endif()

set_target_properties(mailtransport PROPERTIES
  VERSION ${GENERIC_LIB_VERSION}
  SOVERSION ${GENERIC_LIB_SOVERSION}
)

install(TARGETS mailtransport EXPORT kdepimlibsLibraryTargets ${INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES mailtransport.kcfg DESTINATION ${KCFG_INSTALL_DIR})

set(mailtransport_kcm_srcs configmodule.cpp)
kde4_add_plugin(kcm_mailtransport ${mailtransport_kcm_srcs})
target_link_libraries(kcm_mailtransport ${KDE4_KDEUI_LIBS} mailtransport)

install(TARGETS kcm_mailtransport DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES kcm_mailtransport.desktop DESTINATION ${SERVICES_INSTALL_DIR})

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/mailtransport_export.h

  transportjob.h
  sendmailjob.h
  smtpjob.h
  precommandjob.h
  socket.h

  ${CMAKE_CURRENT_BINARY_DIR}/transportbase.h
  transport.h
  transportmanager.h
  transporttype.h
  servertest.h

  transportcombobox.h
  transportconfigdialog.h
  transportmanagementwidget.h

  DESTINATION ${INCLUDE_INSTALL_DIR}/mailtransport COMPONENT Devel
)

if (NOT KDEPIM_NO_AKONADI)
install(FILES
  dispatcherinterface.h
  messagequeuejob.h

  dispatchmodeattribute.h
  errorattribute.h
  sentactionattribute.h
  sentbehaviourattribute.h
  transportattribute.h

  DESTINATION ${INCLUDE_INSTALL_DIR}/mailtransport COMPONENT Devel
)
endif()
