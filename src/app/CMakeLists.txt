project(Kemai)

add_executable(${PROJECT_NAME} ${OS_BUNDLE})

set(SRCS
        activitydialog.cpp
        activitywidget.cpp
        customerdialog.cpp
        datareader.cpp
        durationedit.cpp
        main.cpp
        mainwindow.cpp
        projectdialog.cpp
        settingsdialog.cpp
        taskwidget.cpp)

set(HDRS
        activitydialog.h
        activitywidget.h
        customerdialog.h
        datareader.h
        durationedit.h
        mainwindow.h
        projectdialog.h
        settingsdialog.h
        taskwidget.h)

set(UIS
        activitydialog.ui
        activitywidget.ui
        customerdialog.ui
        mainwindow.ui
        projectdialog.ui
        settingsdialog.ui
        taskwidget.ui)

# Localization
include(LocalizationTools)
set(KEMAI_TS_FILES
        l10n/kemai_de.ts
        l10n/kemai_el.ts
        l10n/kemai_fr.ts
        l10n/kemai_hr.ts
        l10n/kemai_nb_NO.ts)
qt_add_translation(KEMAI_QM_FILES ${KEMAI_TS_FILES})
add_qm_files_to_qrc(KEMAI_L10N_QRC ${KEMAI_QM_FILES})

# Update .ts files on demand
get_target_property(_lupdate_executable Qt::lupdate IMPORTED_LOCATION)
add_custom_target(kemai-update-ts COMMAND
        ${_lupdate_executable} -no-obsolete ${CMAKE_CURRENT_SOURCE_DIR} -ts ${KEMAI_TS_FILES}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(RESX
        data.qrc
        icons.qrc
        ${KEMAI_L10N_QRC})

if (WIN32)
    list(APPEND SRCS ${CMAKE_SOURCE_DIR}/bundle/windows/kemai.rc)
elseif (APPLE)
    set(KEMAI_ICNS "${CMAKE_SOURCE_DIR}/bundle/macos/kemai.icns")
    set_source_files_properties(${KEMAI_ICNS} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/bundle/macos/Info.plist)
endif ()

target_sources(${PROJECT_NAME} PRIVATE ${SRCS} ${HDRS} ${UIS} ${RESX} ${KEMAI_ICNS})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} Qt::Widgets KemaiCore)
