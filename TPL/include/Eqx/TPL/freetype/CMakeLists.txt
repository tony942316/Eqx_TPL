cmake_minimum_required(VERSION 3.28)

FetchContent_Declare(
    freetype
    GIT_REPOSITORY https://github.com/freetype/freetype.git
    GIT_TAG master)

FetchContent_MakeAvailable(freetype)

add_library(Eqx_TPL_freetype INTERFACE)
target_sources(Eqx_TPL_freetype INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/freetype.hpp)
target_compile_features(Eqx_TPL_freetype INTERFACE cxx_std_20)
target_include_directories(Eqx_TPL_freetype INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../include/)
target_link_libraries(Eqx_TPL_freetype INTERFACE freetype)

add_library(Eqx_TPL_freetype_Typical INTERFACE)
target_sources(Eqx_TPL_freetype_Typical INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/freetype.hpp)
target_compile_features(Eqx_TPL_freetype_Typical INTERFACE cxx_std_20)
target_include_directories(Eqx_TPL_freetype_Typical INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../include/)
target_link_libraries(Eqx_TPL_freetype_Typical INTERFACE Eqx_Typical freetype)
