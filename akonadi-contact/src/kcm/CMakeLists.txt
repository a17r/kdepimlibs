
########### next target ###############

set(kcm_akonadicontact_actions_SRCS
    kcmakonadicontactactions.cpp)

ki18n_wrap_ui(kcm_akonadicontact_actions_SRCS akonadicontactactions.ui)

configure_file( ../actions/contactactionssettings.kcfg.cmake ${CMAKE_CURRENT_BINARY_DIR}/contactactionssettings.kcfg @ONLY)
kconfig_add_kcfg_files(kcm_akonadicontact_actions_SRCS ../actions/contactactionssettings.kcfgc)


add_library(kcm_akonadicontact_actions MODULE ${kcm_akonadicontact_actions_SRCS})
#kcoreaddons_desktop_to_json(kcm_akonadicontact_actions akonadicontact_actions.desktop DEFAULT_SERVICE_TYPE)

target_link_libraries(kcm_akonadicontact_actions KF5::ConfigWidgets KF5::I18n KF5::Completion) 



install(TARGETS kcm_akonadicontact_actions DESTINATION ${KDE_INSTALL_PLUGINDIR})

########### install files ###############

install(FILES akonadicontact_actions.desktop DESTINATION ${KDE_INSTALL_KSERVICES5DIR})
