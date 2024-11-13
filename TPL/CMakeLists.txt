cmake_minimum_required(VERSION 3.28)

FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG master)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG master)

FetchContent_Declare(
    freetype
    GIT_REPOSITORY https://github.com/freetype/freetype.git
    GIT_TAG master)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG master)
set(GLFW_BUILD_DOCS Off CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS Off CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES Off CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(stb glm freetype glfw)

add_library(Eqx_TPL_GMF INTERFACE)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
else ()
target_compile_options(Eqx_TPL_GMF INTERFACE
    -fretain-comments-from-system-headers)
endif()

add_subdirectory(include/Eqx/TPL/freetype/)
add_subdirectory(include/Eqx/TPL/glad/)
add_subdirectory(include/Eqx/TPL/glfw/)
add_subdirectory(include/Eqx/TPL/glm/)
add_subdirectory(include/Eqx/TPL/stb/)

add_library(Eqx_TPL INTERFACE)
target_include_directories(Eqx_TPL INTERFACE include)
target_link_libraries(Eqx_TPL INTERFACE Eqx_Stb Eqx_Glfw Eqx_Glad Eqx_Glm
    Eqx_FreeType Eqx_TPL_GMF)
