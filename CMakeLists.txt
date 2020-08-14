cmake_minimum_required(VERSION 3.13.4)

# Enable C++11
if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 11)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Slicer sources
include(FetchContent)
if(NOT DEFINED slicersources_SOURCE_DIR)
  # Download Slicer sources and set variables slicersources_SOURCE_DIR and slicersources_BINARY_DIR
  FetchContent_Populate(slicersources
    GIT_REPOSITORY git://github.com/Slicer/Slicer
    GIT_TAG        1ed419ef83bebe918cefbf78039cfc9d84967571
    GIT_PROGRESS   1
    )
else()
  set(slicersources_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/slicersources-subbuild)
endif()

# macOS initialization
set(CMAKE_MODULE_PATH ${slicersources_SOURCE_DIR}/CMake ${CMAKE_MODULE_PATH})
include(SlicerInitializeOSXVariables)

project(SlicerAstro)

# Configure Application
set(Slicer_APPLICATIONS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Applications)
set(Slicer_MAIN_PROJECT "SlicerAstroApp")

# Set organization
set(Slicer_ORGANIZATION_DOMAIN "punzodavide@hotmail.it")
set(Slicer_ORGANIZATION_NAME   "KapteynAstronomicalInstitute")

# Default home and favorite modules
set(Slicer_DEFAULT_HOME_MODULE "AstroWelcome")
set(Slicer_DEFAULT_FAVORITE_MODULES "AstroWelcome, AstroSampleData, SlicerAstroDataProbe, AstroVolume, AstroSmoothing, AstroMasking, AstroProfiles, AstroMomentMaps, AstroPVSlice, AstroPVDiagram, AstroModeling, AstroReproject")

# Configure SuperBuild
set(SUPERBUILD_TOPLEVEL_PROJECT Slicer)
set(EXTERNAL_PROJECT_ADDITIONAL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SuperBuild")
include(ExternalProjectDependency)

# Additional Slicer dependencies looked up in EXTERNAL_PROJECT_ADDITIONAL_DIR
set(Slicer_ADDITIONAL_DEPENDENCIES
  )


if(NOT CMAKE_CONFIGURATION_TYPES)
  set(Slicer_DEFAULT_BUILD_TYPE "Release")
endif()
include(SlicerInitializeBuildType)
include(SlicerInitializeReleaseType)

# Installation folder and admin account requirement for Windows
if(WIN32)
  # Note: To avoid escaping issue, make sure to use forward slash when setting
  #       "Slicer_CPACK_NSIS_INSTALL_ROOT". It is replaced by "\\\\" in SlicerCPack.
  set(Slicer_CPACK_NSIS_INSTALL_REQUIRES_ADMIN_ACCOUNT ON)
  if(Slicer_CPACK_NSIS_INSTALL_REQUIRES_ADMIN_ACCOUNT)
    # User has administrative privileges, therefore we can install to shared folder
    # "C:\Program Files" or "C:\Program Files (x86)".
    if(CMAKE_CL_64)
      set(Slicer_CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
    else()
      set(Slicer_CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
    endif()
  else()
    # We do not require administrative privileges, therefore we install to user folder
    # "C:\Users\<username>\AppData\Local".
    set(Slicer_CPACK_NSIS_INSTALL_ROOT "$LOCALAPPDATA/${Slicer_ORGANIZATION_NAME}")
  endif()
endif()


# Slicer options
option(BUILD_TESTING                            "Build application test suite"                        ON)
option(Slicer_BUILD_DOCUMENTATION               "Build documentation (Doxygen, sphinx, ...)"          OFF)
if(WIN32)
  option(Slicer_BUILD_WIN32_CONSOLE             "Build application executable as a console app"       OFF)
endif()

option(Slicer_BUILD_CLI                         "Build application with CLI modules"                  OFF)
option(Slicer_BUILD_CLI_SUPPORT                 "Build application with CLI modules support"          ON)
option(Slicer_BUILD_DICOM_SUPPORT               "Build application with DICOM support"                OFF)
option(Slicer_BUILD_DIFFUSION_SUPPORT           "Build application with Diffusion support"            OFF)
option(Slicer_BUILD_EXTENSIONMANAGER_SUPPORT    "Build application with ExtensionManager support"     OFF)
option(Slicer_BUILD_MULTIVOLUME_SUPPORT         "Build application with MultiVolume support"          OFF)
option(Slicer_BUILD_PARAMETERSERIALIZER_SUPPORT "Build application with parameter serializer support" OFF)
option(Slicer_BUILD_WEBENGINE_SUPPORT           "Build application with Qt WebEngine support"         OFF)
option(Slicer_USE_PYTHONQT                      "Build application with Python support"               ON)
option(Slicer_USE_PYTHONQT_WITH_TCL             "Build application with Python Tcl adapter layer"     OFF)
option(Slicer_USE_QtTesting                     "Build application with QtTesting support"            OFF)
option(Slicer_USE_SimpleITK                     "Build application with SimpleITK support"            OFF)

set(Slicer_VTK_SMP_IMPLEMENTATION_TYPE "Sequential" CACHE STRING "" FORCE)

option(Slicer_BUILD_BRAINSTOOLS                 "Build application with BRAINSTools module"           OFF)
option(Slicer_BUILD_DataStore                   "Build application with DataStore module"             OFF)
option(Slicer_BUILD_CompareVolumes              "Build application with ChangeTrackerPy module"       OFF)
option(Slicer_BUILD_LandmarkRegistration        "Build application with LandmarkRegistration module"  OFF)

# Addition Slicer dependencies
set(Slicer_ADDITIONAL_DEPENDENCIES
  )

# Enable Slicer built-in modules
set(Slicer_CLIMODULES_ENABLED
  )
set(Slicer_QTLOADABLEMODULES_ENABLED
  )
set(Slicer_QTSCRIPTEDMODULES_ENABLED
  )

# Disable Slicer built-in modules
set(Slicer_CLIMODULES_DISABLED
  ResampleDTIVolume
  ResampleScalarVectorDWIVolume
  )
set(Slicer_QTLOADABLEMODULES_DISABLED
  CropVolume
  SampleData
  SceneViews
  Sequences
  SlicerWelcome
  )
set(Slicer_QTSCRIPTEDMODULES_DISABLED
  CropVolumeSequence
  Editor
  EditorLib
  Endoscopy
  LabelStatistics
  PerformanceTests
  SampleData
  SegmentStatistics
  VectorToScalarVolume
  NeurosurgicalPlanningTutorialMarkupsSelfTest
  )

#-----------------------------------------------------------------------------
# SlicerAstro extension
set(SlicerAstro_BUILD_TESTING ON)
mark_as_superbuild(SlicerAstro_BUILD_TESTING:BOOL)

set(extension_name "SlicerAstro")
set(${extension_name}_SOURCE_DIR "${CMAKE_BINARY_DIR}/${extension_name}")
FetchContent_Populate(${extension_name}
  SOURCE_DIR	 ${${extension_name}_SOURCE_DIR}
  GIT_REPOSITORY ${EP_GIT_PROTOCOL}://github.com/Punzo/${extension_name}
  GIT_TAG	 1da6c116619f9ea65953e949874c2e83dd176198
  GIT_PROGRESS	 1
  QUIET
  )
list(APPEND Slicer_EXTENSION_SOURCE_DIRS ${${extension_name}_SOURCE_DIR})

#-----------------------------------------------------------------------------
# Add Slicer sources
add_subdirectory(${slicersources_SOURCE_DIR} ${slicersources_BINARY_DIR})
