cmake_minimum_required(VERSION 3.28)

FetchContent_GetProperties(
    glm
    SOURCE_DIR glm_source_dir)

add_library(Eqx_Glm INTERFACE)
target_sources(Eqx_Glm INTERFACE glm.hpp)
target_include_directories(Eqx_Glm INTERFACE ${glm_source_dir}/)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
else ()
add_custom_target("P_EQX_CT_GLM"
    DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/glm.pcm")

add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/glm.pcm"
    COMMENT "Build glm Header Unit"
    COMMAND clang++ -std=c++20
        $<TARGET_PROPERTY:Eqx_TPL_GMF,INTERFACE_COMPILE_OPTIONS>
        -I${CMAKE_CURRENT_SOURCE_DIR}/
        -xc++-system-header --precompile glm.hpp
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/glm.hpp"
    COMMAND_EXPAND_LISTS)

add_library(P_EQX_HU_GLM INTERFACE)
add_dependencies(P_EQX_HU_GLM P_EQX_CT_GLM)
target_compile_options(P_EQX_HU_GLM INTERFACE
    -Wno-experimental-header-units
    -fmodule-file=${CMAKE_CURRENT_BINARY_DIR}/glm.pcm)

target_link_libraries(Eqx_Glm INTERFACE P_EQX_HU_GLM)
endif()
