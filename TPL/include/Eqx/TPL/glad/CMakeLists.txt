cmake_minimum_required(VERSION 3.28)

add_library(Eqx_TPL_glad STATIC)
target_sources(Eqx_TPL_glad PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/glad.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/include/glad/glad.h
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c)
target_compile_features(Eqx_TPL_glad PUBLIC cxx_std_20)
target_include_directories(Eqx_TPL_glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)

add_library(Eqx_TPL_glad_Typical STATIC)
target_sources(Eqx_TPL_glad_Typical PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/glad.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/include/glad/glad.h
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c)
target_compile_features(Eqx_TPL_glad_Typical PUBLIC cxx_std_20)
target_include_directories(Eqx_TPL_glad_Typical PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)
target_link_libraries(Eqx_TPL_glad_Typical PUBLIC Eqx_Typical)

if (Eqx_Clang)
    add_custom_command(
        OUTPUT
            ${CMAKE_CURRENT_BINARY_DIR}/glad_$<CONFIG>.pcm
        COMMAND ${CMAKE_CXX_COMPILER}
            -std=c++20 -fmodule-header
            -I${CMAKE_CURRENT_SOURCE_DIR}/glad/include
            $<TARGET_PROPERTY:Eqx_Typical,INTERFACE_COMPILE_OPTIONS>
            ${CMAKE_CURRENT_SOURCE_DIR}/glad.hpp -o
            ${CMAKE_CURRENT_BINARY_DIR}/glad_$<CONFIG>.pcm
        DEPENDS
            ${CMAKE_CURRENT_SOURCE_DIR}/glad.hpp
        COMMENT "Building glad module"
        COMMAND_EXPAND_LISTS)

    add_custom_target(Eqx_PT_TPL_glad DEPENDS
        ${CMAKE_CURRENT_BINARY_DIR}/glad_$<CONFIG>.pcm)

    target_compile_options(Eqx_TPL_glad INTERFACE
        -Wno-experimental-header-units
        -fmodule-file=${CMAKE_CURRENT_BINARY_DIR}/glad_$<CONFIG>.pcm)
    add_dependencies(Eqx_TPL_glad Eqx_PT_TPL_glad)
elseif (Eqx_GNU)
elseif (Eqx_MSVC)
endif()
