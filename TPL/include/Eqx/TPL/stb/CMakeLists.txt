cmake_minimum_required(VERSION 3.28)

FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG master)

FetchContent_MakeAvailable(stb)

FetchContent_GetProperties(
    stb
    SOURCE_DIR stb_source_dir)

add_library(Eqx_TPL_stb STATIC)
target_sources(Eqx_TPL_stb PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/stb_image.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stb_image.hpp)
target_include_directories(Eqx_TPL_stb PUBLIC ${stb_source_dir}/)

add_library(Eqx_TPL_stb_Typical STATIC)
target_sources(Eqx_TPL_stb_Typical PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/stb_image.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stb_image.hpp)
target_include_directories(Eqx_TPL_stb_Typical PUBLIC ${stb_source_dir}/)
target_link_libraries(Eqx_TPL_stb_Typical PUBLIC Eqx_Typical)
