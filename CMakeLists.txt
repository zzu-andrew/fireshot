cmake_minimum_required(VERSION 3.12)
project(fireshot)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(ui ${CMAKE_SOURCE_DIR}/forms)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${ui})


set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets Network)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network)

#宏定义在这里添加
#add_definitions(
#        -D_ENABLE_LOGGING
#)
add_compile_options(-D USE_SPDLOG_)

if(WIN32)
    set(CMAKE_PREFIX_PATH "D:/software/Qt5.13.0/mingw73_64/lib/cmake/Qt5")
    set(QT_QMAKE_EXECUTABLE "D:/software/Qt/5.13.0/mingw73_64/bin")
else()
    set(CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/cmake/Qt5")
endif()


if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()


#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_DIR})
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_DIR})
#set(CMAKE_PDB_OUTPUT_DIRECTORY ${LIB_DIR})
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${LIB_DIR})

#set(RESOURCE_SOURCES
#        source/qml/qml.qrc
#        #        source/image/image.qrc
#        )
#set(QML_SOURCES
#        source/qml/main.qml)

## 添加用户界面文件
#set(FORMS
#        mainwindow.ui
#        )

# 自动生成用户界面文件的 C++ 代码
#qt5_wrap_ui(UI_HEADERS ${FORMS})

# 自动生成用户界面文件的 C++ 代码
# 自动生成用户界面文件的 C++ 代码
#set(UI_HEADERS)
if(WIN32)


else(UNIX)

endif()

set(ui_files
        ${CMAKE_CURRENT_SOURCE_DIR}/forms/tray_settings.ui
        )

set(qrc_files
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/res.qrc)

#find_package(Qt5Widgets REQUIRED QUIET)
#
#QT5_WRAP_UI  (project_FORMS_HEADERS forms/tray_setting.ui)
#QT5_ADD_RESOURCES (project_RESOURCE_CPPS **.qrc)


#  add core
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/core core_src)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/utils utils_src)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/config config_src)

add_executable(${PROJECT_NAME}
        main.cpp
        fireshot.cpp
        ${core_src}
        ${utils_src}
        ${config_src}
        )

target_sources(
        ${PROJECT_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/forms/tray_settings.ui
            ${qrc_files}
)
#find_package(PkgConfig REQUIRED)
#pkg_search_module(GTK REQUIRED gtk+-3.0)
#
#include_directories(${GTK_INCLUDE_DIRS})
#link_directories(${GTK_LIBRARY_DIRS})
#target_link_libraries(${PROJECT_NAME} ${GTK_LIBRARIES})

#if(WIN32)
#    target_link_libraries(${PROJECT_NAME} xcb xcb-util)
#endif()

target_include_directories(${PROJECT_NAME}
    PUBLIC ./
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_autogen/include
        ${CMAKE_CURRENT_SOURCE_DIR}/3rd)


find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})



