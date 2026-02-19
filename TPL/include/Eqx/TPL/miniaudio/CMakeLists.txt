# CMakeLists.txt

cmake_minimum_required(VERSION 3.28)

FetchContent_Declare(
    miniaudio
    GIT_REPOSITORY https://github.com/mackron/miniaudio.git
    GIT_TAG master)

FetchContent_MakeAvailable(miniaudio)

FetchContent_GetProperties(
    miniaudio
    SOURCE_DIR miniaudio_source_dir)

add_library(Eqx_TPL_miniaudio STATIC)
target_sources(Eqx_TPL_miniaudio PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/miniaudio.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/miniaudio.hpp)
target_include_directories(Eqx_TPL_miniaudio PUBLIC
    ${miniaudio_source_dir}/
    ${CMAKE_CURRENT_SOURCE_DIR}/)
target_compile_definitions(Eqx_TPL_miniaudio PRIVATE MA_NO_DSOUND)

add_library(Eqx_TPL_miniaudio_Typical STATIC)
target_sources(Eqx_TPL_miniaudio_Typical PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/miniaudio.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/miniaudio.hpp)
target_include_directories(Eqx_TPL_miniaudio_Typical PUBLIC
    ${miniaudio_source_dir}/
    ${CMAKE_CURRENT_SOURCE_DIR}/)
target_compile_definitions(Eqx_TPL_miniaudio_Typical PRIVATE MA_NO_DSOUND)
target_link_libraries(Eqx_TPL_miniaudio_Typical PUBLIC Eqx_Typical)
