cmake_minimum_required(VERSION 3.28)

add_library(Eqx_Stb STATIC)
target_sources(Eqx_Stb PRIVATE stb_image.c stb_image.hpp)
target_include_directories(Eqx_Stb PUBLIC ../../../../Dependencies/stb/)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
else ()
add_custom_target("P_EQX_CT_STB"
    DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/stb_image.pcm")

add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/stb_image.pcm"
    COMMENT "Build stb_image Header Unit"
    COMMAND clang++ -std=c++20
        $<TARGET_PROPERTY:Eqx_TPL_GMF,INTERFACE_COMPILE_OPTIONS>
        -I${CMAKE_CURRENT_SOURCE_DIR}/../../../../Dependencies/stb/
        -I${CMAKE_CURRENT_SOURCE_DIR}/
        -xc++-system-header --precompile stb_image.hpp
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/stb_image.hpp"
    COMMAND_EXPAND_LISTS)

add_library(P_EQX_HU_STB INTERFACE)
add_dependencies(P_EQX_HU_STB P_EQX_CT_STB)
target_compile_options(P_EQX_HU_STB INTERFACE
    -Wno-experimental-header-units
    -fmodule-file=${CMAKE_CURRENT_BINARY_DIR}/stb_image.pcm)

target_link_libraries(Eqx_Stb INTERFACE P_EQX_HU_STB)
endif()
