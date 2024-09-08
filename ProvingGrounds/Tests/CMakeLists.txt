cmake_minimum_required(VERSION 3.28)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
else ()
    add_custom_target(P_EQX_CT_STDLIB
        DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/Stdlib.pcm")

    add_custom_command(
        OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/Stdlib.pcm"
        COMMENT "Build Stdlib Header Unit"
        COMMAND clang++ -std=c++20
            $<TARGET_PROPERTY:Eqx_TPL_GMF,INTERFACE_COMPILE_OPTIONS>
            -Wno-user-defined-literals
            -Wno-implicit-int-conversion
            -Wno-shorten-64-to-32
            -Wno-sign-conversion
            -Wno-unknown-warning-option
            -Wno-inline-namespace-reopened-noninline
            -Wno-deprecated-builtins
            -Wno-implicit-float-conversion
            -Wno-keyword-compat
            -Wno-gnu-include-next
            -Wno-ambiguous-ellipsis
            -Wno-pragma-system-header-outside-header

            -I${CMAKE_CURRENT_SOURCE_DIR}/include
            -xc++-system-header --precompile Stdlib.hpp
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/Stdlib.hpp"
        COMMAND_EXPAND_LISTS)

    add_library(P_EQX_HU_STDLIB INTERFACE)
    add_dependencies(P_EQX_HU_STDLIB P_EQX_CT_STDLIB)
    target_compile_options(P_EQX_HU_STDLIB INTERFACE
        -Wno-experimental-header-units
        -fmodule-file=${CMAKE_CURRENT_BINARY_DIR}/Stdlib.pcm)
endif()

add_library(Tests STATIC)
target_sources(Tests
    PUBLIC FILE_SET CXX_MODULES FILES
        Tests.cpp
        FreeType.cpp
        Glad.cpp
        Glfw.cpp
        Glm.cpp
        Stb_Image.cpp)
target_compile_features(Tests PUBLIC cxx_std_20)
target_include_directories(Tests PUBLIC include/)
target_link_libraries(Tests PRIVATE Eqx_TPL)
set_target_properties(Tests PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)

add_custom_command(TARGET Tests PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/../Resources
        $<TARGET_FILE_DIR:ProvingGrounds>/Resources
    COMMENT "Copying Resources")

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
else ()
    target_link_libraries(Tests PUBLIC P_EQX_HU_STDLIB)
endif()
