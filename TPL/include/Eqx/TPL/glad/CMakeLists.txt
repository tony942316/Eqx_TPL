cmake_minimum_required(VERSION 3.28)

add_library(Eqx_Glad STATIC)
target_sources(Eqx_Glad PRIVATE glad.hpp glad/src/glad.c)
target_include_directories(Eqx_Glad PUBLIC glad/include/)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
else ()
add_custom_target("P_EQX_CT_GLAD"
    DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/glad.pcm")

add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/glad.pcm"
    COMMENT "Build glad Header Unit"
    COMMAND clang++ -std=c++20
        $<TARGET_PROPERTY:Eqx_TPL_GMF,INTERFACE_COMPILE_OPTIONS>
        -I${CMAKE_CURRENT_SOURCE_DIR}/glad/include/
        -I${CMAKE_CURRENT_SOURCE_DIR}/
        -xc++-system-header --precompile glad.hpp
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/glad.hpp"
    COMMAND_EXPAND_LISTS)

add_library(P_EQX_HU_GLAD INTERFACE)
add_dependencies(P_EQX_HU_GLAD P_EQX_CT_GLAD)
target_compile_options(P_EQX_HU_GLAD INTERFACE
    -Wno-experimental-header-units
    -fmodule-file=${CMAKE_CURRENT_BINARY_DIR}/glad.pcm)

target_link_libraries(Eqx_Glad INTERFACE P_EQX_HU_GLAD)
endif()
