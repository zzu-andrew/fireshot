find_package(
        Qt5
        CONFIG
        REQUIRED
        Core
        Gui
        Widgets
        Network
        Svg
        DBus
        LinguistTools)

if (USE_WAYLAND_CLIPBOARD)
    find_package(KF5GuiAddons)
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# set application icon

add_executable(fireshot)

add_executable(Flameshot::fireshot ALIAS fireshot)

if(FLAMESHOT_ICON)
  target_compile_definitions(fireshot PUBLIC FLAMESHOT_ICON="${FLAMESHOT_ICON}")
endif()

if (WIN32)
    set_property(TARGET fireshot PROPERTY WIN32_EXECUTABLE true)
    if (MSVC)
        target_compile_options(fireshot PRIVATE /source-charset:utf-8)
    endif ()
endif ()

if(MSVC)
    OPTION(USE_MP "use multiple" ON)
    OPTION(ProjectConfig_Global_COMPILE_FLAGS_WITH_MP
            "Set The Global Option COMPILE_FLAGS /MP to target." ON)
    if(ProjectConfig_Global_COMPILE_FLAGS_WITH_MP OR USE_MP)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
    endif()
endif()

add_subdirectory(cli)
add_subdirectory(config)
add_subdirectory(core)
add_subdirectory(utils)
add_subdirectory(widgets)
add_subdirectory(tools)


set(FLAMESHOT_TS_FILES
      ${CMAKE_SOURCE_DIR}/data/translations/Internationalization_zh_CN.ts
         )

if (GENERATE_TS)
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${FLAMESHOT_TS_FILES})
else ()
    qt5_add_translation(QM_FILES ${FLAMESHOT_TS_FILES})
endif ()

target_sources(
        fireshot
        PRIVATE
        # ${CMAKE_CURRENT_SOURCE_DIR}/../external/Qt-Color-Widgets/src/QtColorWidgets/color_utils.cpp
        # ${CMAKE_CURRENT_SOURCE_DIR}/../external/Qt-Color-Widgets/src/QtColorWidgets/color_wheel.cpp
        # ${CMAKE_CURRENT_SOURCE_DIR}/../external/Qt-Color-Widgets/include/QtColorWidgets/color_wheel.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../data/graphics.qrc
        ${CMAKE_CURRENT_SOURCE_DIR}/../data/flameshot.rc # windows binary icon resource file
        ${QM_FILES}
        main.cpp)

target_include_directories(
  fireshot
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../external/Qt-Color-Widgets/include>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../dbus/>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cli>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/config>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/core>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tools>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tools/arrow>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tools/pixelate>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tools/circle>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tools/circlecount>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tools/copy>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tools/exit>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tools/imgur>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tools/launcher>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tools/line>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tools/marker>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tools/move>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tools/pencil>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tools/pin>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tools/rectangle>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tools/redo>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tools/save>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tools/invert>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tools/selection>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tools/sizeindicator>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tools/text>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tools/undo>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tools/sizeincrease>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tools/sizedecrease>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/utils>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/widgets>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/widgets/panel>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/widgets/capture>
         $<INSTALL_INTERFACE:include/mylib>)
target_include_directories(
    fireshot
    PUBLIC
         $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/>
         )


target_include_directories(
    fireshot
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../external/singleapplication>)

target_link_libraries(
        fireshot
        project_warnings
        project_options
        Qt5::Svg
        Qt5::DBus
        Qt5::Network
        Qt5::Widgets
        ${QTSINGLEAPPLICATION_LIBRARY}
        QtColorWidgets

)

if (USE_WAYLAND_CLIPBOARD)
  if(!USE_WAYLAND_GRIM)
    message(WARNING "You activated the USE_WAYLAND_CLIPBOARD option, but did not activate the USE_WAYLAND_GRIM option. Flameshot will use the dbus protocol to support wayland. If you use wlroots-based wayland, it is recommended to enable USE_WAYLAND_GRIM")
  endif()
  target_compile_definitions(fireshot PRIVATE USE_WAYLAND_CLIPBOARD=1)
  target_link_libraries(fireshot KF5::GuiAddons)
endif()

if (USE_WAYLAND_GRIM)
    target_compile_definitions(fireshot PRIVATE USE_WAYLAND_GRIM=1)
endif()

set(_src_root_path ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE _source_list LIST_DIRECTORIES false
    "${_src_root_path}/*.cpp"
    "${_src_root_path}/*.h")

#  will be organized according to the actual directory structure, .h.cpp is put together
source_group(TREE ${_src_root_path} FILES ${_source_list})

if (WIN32)
    set(USE_OPENSSL FALSE)
    if (ENABLE_OPENSSL)
        find_package(OpenSSL)
        if (OPENSSL_FOUND)
            message(STATUS "OpenSSL support enabled.")
            set(USE_OPENSSL TRUE)
        endif ()
    else ()
        mark_as_advanced(CLEAR OPENSSL_LIBRARIES OPENSSL_INCLUDE_DIR)
    endif ()

    if (NOT USE_OPENSSL)
        message(WARNING "OpenSSL is required to upload screenshots")
    endif ()
endif ()

# Choose default color palette (small or large)
if($ENV{FLAMESHOT_PREDEFINED_COLOR_PALETTE_LARGE})
    set(FLAMESHOT_PREDEFINED_COLOR_PALETTE_LARGE true)
else()
    set(FLAMESHOT_PREDEFINED_COLOR_PALETTE_LARGE false)
endif()
message("Flameshot predefined color palette large: " ${FLAMESHOT_PREDEFINED_COLOR_PALETTE_LARGE})
target_compile_definitions(fireshot PRIVATE PREDEFINED_COLOR_PALETTE_LARGE=${FLAMESHOT_PREDEFINED_COLOR_PALETTE_LARGE})

# 查找git并获取git版本以及当前目录的hash值
find_package (Git)
if (GIT_FOUND)
    message("git found: ${GIT_EXECUTABLE} in version     ${GIT_VERSION_STRING}")
    #  git rev-parse --short HEAD
    execute_process(COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD OUTPUT_VARIABLE FLAMESHOT_GIT_HASH)
    string(REGEX REPLACE "\r*\n$" "" FLAMESHOT_GIT_HASH "${FLAMESHOT_GIT_HASH}")
    target_compile_definitions(fireshot PRIVATE FLAMESHOT_GIT_HASH="${FLAMESHOT_GIT_HASH}")
    message("FLAMESHOT_GIT_HASH: ${FLAMESHOT_GIT_HASH}")
else()
    target_compile_definitions(fireshot PRIVATE FLAMESHOT_GIT_HASH="-")
    message("git command is not found")
endif ()


target_compile_definitions(fireshot PRIVATE APP_PREFIX="${CMAKE_INSTALL_PREFIX}")
target_compile_definitions(fireshot PRIVATE APP_VERSION="v${PROJECT_VERSION}")

if (FLAMESHOT_DEBUG_CAPTURE)
    target_compile_definitions(fireshot PRIVATE FLAMESHOT_DEBUG_CAPTURE)
endif ()


foreach (FILE ${QM_FILES})
    get_filename_component(F_NAME ${FILE} NAME)
    add_custom_command(
            TARGET fireshot
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/${F_NAME}
            ${CMAKE_CURRENT_BINARY_DIR}/translations/${F_NAME})
endforeach ()

# ######################################################################################################################
# Installation instructions

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/Flameshot)

if(USE_LAUNCHER_ABSOLUTE_PATH)
    set(LAUNCHER_EXECUTABLE "${CMAKE_INSTALL_FULL_BINDIR}/fireshot")
else()
    set(LAUNCHER_EXECUTABLE "fireshot")
endif()

# Install binary
install(TARGETS fireshot
        EXPORT fireshot-targets
        BUNDLE DESTINATION ${CMAKE_INSTALL_BINDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})


# windeployqt
if (WIN32)
    if (EXISTS $ENV{QTDIR}/bin/windeployqt.exe)
        if (CMAKE_BUILD_TYPE MATCHES Release)
            set(BINARIES_TYPE --release)
        else ()
            set(BINARIES_TYPE --debug)
        endif ()

        add_custom_command(
                TARGET fireshot
                POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/windeployqt_stuff
                COMMAND
                $ENV{QTDIR}/bin/windeployqt.exe ${BINARIES_TYPE} --no-translations --compiler-runtime --no-system-d3d-compiler
                --no-angle --no-webkit2 --no-quick-import --dir ${CMAKE_BINARY_DIR}/windeployqt_stuff $<TARGET_FILE:fireshot>
                # copy translations manually QM_FILES
                COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/windeployqt_stuff/translations
                COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR}/src/translations
                ${CMAKE_BINARY_DIR}/windeployqt_stuff/translations)

        install(DIRECTORY ${CMAKE_BINARY_DIR}/windeployqt_stuff/ DESTINATION bin)


        STRING(REGEX REPLACE "\\\\" "/" OPENSSL_ROOT_DIR "$ENV{OPENSSL_ROOT_DIR}" )

        if (ENABLE_OPENSSL)
            if (EXISTS ${OPENSSL_ROOT_DIR}/bin)

                install(
                        DIRECTORY ${OPENSSL_ROOT_DIR}/bin/
                        DESTINATION bin
                        FILES_MATCHING
                        PATTERN "*.dll")
            else ()
                message(WARNING "Unable to find OpenSSL dlls.")
            endif ()
        endif ()

    else ()
        message("Unable to find executable QTDIR/bin/windeployqt.")
    endif ()
endif ()


