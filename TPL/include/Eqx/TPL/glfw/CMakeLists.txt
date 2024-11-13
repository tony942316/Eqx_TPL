cmake_minimum_required(VERSION 3.28)

add_library(Eqx_Glfw INTERFACE)
target_sources(Eqx_Glfw INTERFACE glfw.hpp)
target_link_libraries(Eqx_Glfw INTERFACE glfw)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
else ()
add_custom_target("P_EQX_CT_GLFW"
    DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/glfw.pcm")

add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/glfw.pcm"
    COMMENT "Build glfw Header Unit"
    COMMAND clang++ -std=c++20
        $<TARGET_PROPERTY:Eqx_TPL_GMF,INTERFACE_COMPILE_OPTIONS>
        -I${CMAKE_CURRENT_SOURCE_DIR}/
        -xc++-system-header --precompile glfw.hpp
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/glfw.hpp"
    COMMAND_EXPAND_LISTS)

add_library(P_EQX_HU_GLFW INTERFACE)
add_dependencies(P_EQX_HU_GLFW P_EQX_CT_GLFW)
target_compile_options(P_EQX_HU_GLFW INTERFACE
    -Wno-experimental-header-units
    -fmodule-file=${CMAKE_CURRENT_BINARY_DIR}/glfw.pcm)

target_link_libraries(Eqx_Glfw INTERFACE P_EQX_HU_GLFW)
endif()
