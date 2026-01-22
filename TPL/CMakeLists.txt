cmake_minimum_required(VERSION 3.28)

FetchContent_Declare(
    Eqx_CMakeInterfaces
    GIT_REPOSITORY https://github.com/tony942316/Eqx_CMakeInterfaces.git
    GIT_TAG main)

FetchContent_Declare(
    Eqx_Std
    GIT_REPOSITORY https://github.com/tony942316/Eqx_Std.git
    GIT_TAG main)

FetchContent_MakeAvailable(Eqx_CMakeInterfaces Eqx_Std)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/include/Eqx/TPL/glfw/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/include/Eqx/TPL/glad/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/include/Eqx/TPL/stb/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/include/Eqx/TPL/glm/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/include/Eqx/TPL/freetype/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Wrapper/glfw/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Wrapper/glad/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Wrapper/stb_image/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Wrapper/glm/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Wrapper/freetype/)

add_library(Eqx_TPL INTERFACE)
target_include_directories(Eqx_TPL INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_link_libraries(Eqx_TPL INTERFACE Eqx_TPL_glfw Eqx_TPL_glad Eqx_TPL_stb
    Eqx_TPL_glm Eqx_TPL_freetype Eqx_TPL_Wrapper_glfw Eqx_TPL_Wrapper_glad
    Eqx_TPL_Wrapper_stb_image Eqx_TPL_Wrapper_glm Eqx_TPL_Wrapper_freetype)

add_library(Eqx_TPL_Typical INTERFACE)
target_include_directories(Eqx_TPL_Typical INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_link_libraries(Eqx_TPL_Typical INTERFACE Eqx_Typical Eqx_TPL_glfw_Typical
    Eqx_TPL_glad_Typical Eqx_TPL_stb_Typical Eqx_TPL_glm_Typical
    Eqx_TPL_freetype_Typical Eqx_TPL_Wrapper_glfw_Typical
    Eqx_TPL_Wrapper_glad_Typical Eqx_TPL_Wrapper_stb_image_Typical
    Eqx_TPL_Wrapper_glm_Typical Eqx_TPL_Wrapper_freetype_Typical)
