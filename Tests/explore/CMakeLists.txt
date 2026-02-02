cmake_minimum_required(VERSION 3.28)

include(${CMAKE_CURRENT_SOURCE_DIR}/Explore.cmake)

add_executable(Explore)
target_sources(Explore PRIVATE Main.cpp)
target_compile_features(Explore PRIVATE cxx_std_20)
set_target_properties(Explore PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
target_link_libraries(Explore PRIVATE Eqx_Std Eqx_TPL_Tests_Explore
    Eqx_Warnings_Error)

add_executable(Explore_Typical)
target_sources(Explore_Typical PRIVATE Main.cpp)
target_compile_features(Explore_Typical PRIVATE cxx_std_20)
set_target_properties(Explore_Typical PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
target_link_libraries(Explore_Typical PRIVATE Eqx_Std_Typical
    Eqx_TPL_Tests_Explore_Typical Eqx_Warnings_Error)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Resources/Textures/)
configure_file(
    ${CMAKE_SOURCE_DIR}/Resources/Textures/Brick_Wall.png
    ${CMAKE_CURRENT_BINARY_DIR}/Resources/Textures/Brick_Wall.png
    COPYONLY)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Resources/Shaders/)
configure_file(
    ${CMAKE_SOURCE_DIR}/Resources/Shaders/Basic.vs.glsl
    ${CMAKE_CURRENT_BINARY_DIR}/Resources/Shaders/Basic.vs.glsl
    COPYONLY)
configure_file(
    ${CMAKE_SOURCE_DIR}/Resources/Shaders/Basic.fs.glsl
    ${CMAKE_CURRENT_BINARY_DIR}/Resources/Shaders/Basic.fs.glsl
    COPYONLY)
configure_file(
    ${CMAKE_SOURCE_DIR}/Resources/Shaders/Textured_Quad.vs.glsl
    ${CMAKE_CURRENT_BINARY_DIR}/Resources/Shaders/Textured_Quad.vs.glsl
    COPYONLY)
configure_file(
    ${CMAKE_SOURCE_DIR}/Resources/Shaders/Textured_Quad.fs.glsl
    ${CMAKE_CURRENT_BINARY_DIR}/Resources/Shaders/Textured_Quad.fs.glsl
    COPYONLY)
configure_file(
    ${CMAKE_SOURCE_DIR}/Resources/Shaders/MVP_Quad.vs.glsl
    ${CMAKE_CURRENT_BINARY_DIR}/Resources/Shaders/MVP_Quad.vs.glsl
    COPYONLY)
configure_file(
    ${CMAKE_SOURCE_DIR}/Resources/Shaders/MVP_Textured_Quad.vs.glsl
    ${CMAKE_CURRENT_BINARY_DIR}/Resources/Shaders/MVP_Textured_Quad.vs.glsl
    COPYONLY)
configure_file(
    ${CMAKE_SOURCE_DIR}/Resources/Shaders/Text.fs.glsl
    ${CMAKE_CURRENT_BINARY_DIR}/Resources/Shaders/Text.fs.glsl
    COPYONLY)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Resources/Fonts/)
configure_file(
    ${CMAKE_SOURCE_DIR}/Resources/Fonts/Hack-Regular.ttf
    ${CMAKE_CURRENT_BINARY_DIR}/Resources/Fonts/Hack-Regular.ttf
    COPYONLY)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Resources/Sounds/)
configure_file(
    ${CMAKE_SOURCE_DIR}/Resources/Sounds/Mario_Coin.mp3
    ${CMAKE_CURRENT_BINARY_DIR}/Resources/Sounds/Mario_Coin.mp3
    COPYONLY)

eqx_copy_asan(Explore_Typical)
