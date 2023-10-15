

add_library(spdlog STATIC
        spdlog_wrapper.cpp)

target_compile_definitions(spdlog PUBLIC USE_SPDLOG_)

target_include_directories(spdlog PUBLIC ${CMAKE_SOURCE_DIR}/3rd)

