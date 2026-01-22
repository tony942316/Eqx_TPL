cmake_minimum_required(VERSION 3.28)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG master)
set(GLFW_BUILD_DOCS Off CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS Off CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES Off CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)

add_library(Eqx_TPL_glfw INTERFACE)
target_sources(Eqx_TPL_glfw INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/glfw.hpp)
target_include_directories(Eqx_TPL_glfw INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../include/)
target_compile_features(Eqx_TPL_glfw INTERFACE cxx_std_20)
target_link_libraries(Eqx_TPL_glfw INTERFACE glfw)

add_library(Eqx_TPL_glfw_Typical INTERFACE)
target_sources(Eqx_TPL_glfw_Typical INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/glfw.hpp)
target_include_directories(Eqx_TPL_glfw_Typical INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../include/)
target_compile_features(Eqx_TPL_glfw_Typical INTERFACE cxx_std_20)
target_link_libraries(Eqx_TPL_glfw_Typical INTERFACE Eqx_Typical glfw)

if (Eqx_Clang)
    add_custom_command(
        OUTPUT
            ${CMAKE_CURRENT_BINARY_DIR}/glfw_$<CONFIG>.pcm
        COMMAND ${CMAKE_CXX_COMPILER}
            -std=c++20 -fmodule-header
            -I$<TARGET_PROPERTY:glfw,INTERFACE_INCLUDE_DIRECTORIES>
            $<TARGET_PROPERTY:Eqx_Typical,INTERFACE_COMPILE_OPTIONS>
            ${CMAKE_CURRENT_SOURCE_DIR}/glfw.hpp -o
            ${CMAKE_CURRENT_BINARY_DIR}/glfw_$<CONFIG>.pcm
        DEPENDS
            ${CMAKE_CURRENT_SOURCE_DIR}/glfw.hpp
        COMMENT "Building glfw module"
        COMMAND_EXPAND_LISTS)

    add_custom_target(Eqx_PT_TPL_glfw DEPENDS
        ${CMAKE_CURRENT_BINARY_DIR}/glfw_$<CONFIG>.pcm)

    target_compile_options(Eqx_TPL_glfw INTERFACE
        -Wno-experimental-header-units
        -fmodule-file=${CMAKE_CURRENT_BINARY_DIR}/glfw_$<CONFIG>.pcm)
    add_dependencies(Eqx_TPL_glfw Eqx_PT_TPL_glfw)
elseif (Eqx_GNU)
elseif (Eqx_MSVC)
endif()
