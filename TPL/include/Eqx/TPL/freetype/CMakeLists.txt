cmake_minimum_required(VERSION 3.28)

add_library(Eqx_FreeType INTERFACE)
target_sources(Eqx_FreeType INTERFACE freetype.hpp)
target_link_libraries(Eqx_FreeType INTERFACE freetype)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
else ()
    add_custom_target("P_EQX_CT_FREETYPE"
    DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/freetype.pcm")

add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/freetype.pcm"
    COMMENT "Build freetype Header Unit"
    COMMAND clang++ -std=c++20
        $<TARGET_PROPERTY:Eqx_TPL_GMF,INTERFACE_COMPILE_OPTIONS>
        -I${CMAKE_CURRENT_SOURCE_DIR}/
        -xc++-system-header --precompile freetype.hpp
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/freetype.hpp"
    COMMAND_EXPAND_LISTS)

add_library(P_EQX_HU_FREETYPE INTERFACE)
add_dependencies(P_EQX_HU_FREETYPE P_EQX_CT_FREETYPE)
target_compile_options(P_EQX_HU_FREETYPE INTERFACE
    -Wno-experimental-header-units
    -fmodule-file=${CMAKE_CURRENT_BINARY_DIR}/freetype.pcm)

target_link_libraries(Eqx_FreeType INTERFACE P_EQX_HU_FREETYPE)
endif()
