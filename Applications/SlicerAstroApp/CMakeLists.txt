project(SlicerAstroApp)

include(SlicerMacroBuildApplication)

# --------------------------------------------------------------------------
# Properties
# --------------------------------------------------------------------------
SlicerReadApplicationProperties()

# --------------------------------------------------------------------------
# Folder
# --------------------------------------------------------------------------
set(${PROJECT_NAME}_FOLDER "App-${PROJECT_NAME}")

# --------------------------------------------------------------------------
# Application library
# --------------------------------------------------------------------------
set(APPLIB_NAME "q${PROJECT_NAME}")

set(APPLIB_SRCS
  Widgets/qAppStyle.cxx
  Widgets/qAppStyle.h
  Widgets/qSlicerAstroAboutDialog.cxx
  Widgets/qSlicerAstroAboutDialog.h
  qSlicerAstroAppMainWindow.cxx
  qSlicerAstroAppMainWindow.h
  )

set(APPLIB_MOC_SRCS
  Widgets/qAppStyle.h
  Widgets/qSlicerAstroAboutDialog.h
  qSlicerAstroAppMainWindow.h
  )

set(APPLIB_UI_SRCS
  Resources/UI/qSlicerAstroAboutDialog.ui
  )

set(APPLIB_RESOURCES
  Resources/App.qrc
  )

slicerMacroBuildAppLibrary(
  NAME ${APPLIB_NAME}
  DESCRIPTION_SUMMARY ${${PROJECT_NAME}_DESCRIPTION_SUMMARY}
  DESCRIPTION_FILE ${${PROJECT_NAME}_DESCRIPTION_FILE}
  APPLICATION_NAME ${${PROJECT_NAME}_APPLICATION_NAME}
  EXPORT_DIRECTIVE "Q_SLICERASTRO_APP_EXPORT"
  FOLDER ${${PROJECT_NAME}_FOLDER}
  SRCS ${APPLIB_SRCS}
  MOC_SRCS ${APPLIB_MOC_SRCS}
  UI_SRCS ${APPLIB_UI_SRCS}
  RESOURCES ${APPLIB_RESOURCES}
  )

# --------------------------------------------------------------------------
# Application executable
# --------------------------------------------------------------------------

# Configure launcher only for the main application
set(extra_args)
if(${PROJECT_NAME} STREQUAL ${Slicer_MAIN_PROJECT})
  set(extra_args CONFIGURE_LAUNCHER)
endif()

set(APP_SRCS
  Main.cxx
  )

set(APP_TARGET_LIBRARIES ${APPLIB_NAME})

slicerMacroBuildApplication(
  NAME ${PROJECT_NAME}
  APPLICATION_NAME ${${PROJECT_NAME}_APPLICATION_NAME}
  LAUNCHER_SPLASHSCREEN_FILE ${${PROJECT_NAME}_LAUNCHER_SPLASHSCREEN_FILE}
  APPLE_ICON_FILE ${${PROJECT_NAME}_APPLE_ICON_FILE}
  WIN_ICON_FILE ${${PROJECT_NAME}_WIN_ICON_FILE}
  LICENSE_FILE ${${PROJECT_NAME}_LICENSE_FILE}
  FOLDER ${${PROJECT_NAME}_FOLDER}
  SRCS ${APP_SRCS}
  TARGET_LIBRARIES ${APP_TARGET_LIBRARIES}
  TARGET_NAME_VAR "APP_TARGET_NAME"
  ${extra_args}
  )

#-----------------------------------------------------------------------------
# copy SlicerAstro default settings

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/Resources/Settings/SlicerAstroDefaultSettings.ini
  ${CMAKE_BINARY_DIR}/${Slicer_SHARE_DIR}/SlicerAstroDefaultSettings.ini
  COPYONLY)

install(
  FILES ${CMAKE_BINARY_DIR}/${Slicer_SHARE_DIR}/SlicerAstroDefaultSettings.ini
  DESTINATION ${Slicer_INSTALL_SHARE_DIR}
  COMPONENT Runtime)
