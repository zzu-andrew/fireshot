cmake_minimum_required(VERSION 3.13)

set(FIRESHOT_VERSION 1.0.0.0)

project(
        fireshot
        VERSION ${FIRESHOT_VERSION}
        LANGUAGES CXX)

set(PROJECT_NAME_CAPITALIZED "FireShot")


option(FLAMESHOT_DEBUG_CAPTURE "Enable mode to make debugging easier" ON)
option(USE_MONOCHROME_ICON "Build using monochrome icon as default" OFF)
option(GENERATE_TS "Regenerate translation source files" OFF)
option(USE_LAUNCHER_ABSOLUTE_PATH "Use absolute path for the desktop launcher" ON)
option(USE_WAYLAND_CLIPBOARD "USE KF Gui Wayland Clipboard" OFF)


include(cmake/StandardProjectSettings.cmake)

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

add_library(project_warnings INTERFACE)

# enable cache system
include(cmake/Cache.cmake)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
# set_project_warnings(project_warnings)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# allow for static analysis options include(cmake/StaticAnalyzers.cmake)

set(QAPPLICATION_CLASS
        QApplication
        CACHE STRING "Inheritance class for SingleApplication")


add_subdirectory(external/singleapplication)
set(QTSINGLEAPPLICATION_LIBRARY SingleApplication::SingleApplication)


option(BUILD_STATIC_LIBS ON)
option(BUILD_SHARED_LIBS OFF)
add_subdirectory(external/Qt-Color-Widgets EXCLUDE_FROM_ALL) 

add_subdirectory(src)

set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README.md") # TODO: Where is this used? Do we need a better
# source?

if(WIN32)
  # Include all dynamically linked runtime libraries such as MSVCRxxx.dll
  include(InstallRequiredSystemLibraries)

else()
  set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}-linux")
  set(CPACK_GENERATOR TGZ)
  set(CPACK_SOURCE_GENERATOR TGZ)
endif()

include(CPack)
