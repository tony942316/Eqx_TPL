cmake_minimum_required(VERSION 3.28)

FetchContent_Declare(
    Eqx_CMakeInterfaces
    GIT_REPOSITORY https://github.com/tony942316/Eqx_CMakeInterfaces.git
    GIT_TAG main)

FetchContent_MakeAvailable(Eqx_CMakeInterfaces)

add_subdirectory(include/Eqx/TPL/glfw/)
add_subdirectory(include/Eqx/TPL/glad/)
add_subdirectory(include/Eqx/TPL/stb/)
add_subdirectory(include/Eqx/TPL/glm/)

add_library(Eqx_TPL INTERFACE)
target_include_directories(Eqx_TPL INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_link_libraries(Eqx_TPL INTERFACE Eqx_TPL_glfw Eqx_TPL_glad Eqx_TPL_stb
    Eqx_TPL_glm)
