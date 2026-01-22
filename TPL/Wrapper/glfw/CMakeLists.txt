# CMakeLists.txt

cmake_minimum_required(VERSION 3.28)

add_library(Eqx_TPL_Wrapper_glfw STATIC)
target_sources(Eqx_TPL_Wrapper_glfw PUBLIC
    FILE_SET CXX_MODULES FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Window.cpp)
target_compile_features(Eqx_TPL_Wrapper_glfw PUBLIC cxx_std_20)
target_link_libraries(Eqx_TPL_Wrapper_glfw PRIVATE Eqx_Std Eqx_TPL_glfw
    Eqx_TPL_glad)
set_target_properties(Eqx_TPL_Wrapper_glfw PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)

add_library(Eqx_TPL_Wrapper_glfw_Typical STATIC)
target_sources(Eqx_TPL_Wrapper_glfw_Typical PUBLIC
    FILE_SET CXX_MODULES FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Window.cpp)
target_compile_features(Eqx_TPL_Wrapper_glfw_Typical PUBLIC cxx_std_20)
target_link_libraries(Eqx_TPL_Wrapper_glfw_Typical PRIVATE Eqx_Std_Typical
    Eqx_TPL_glfw_Typical Eqx_TPL_glad_Typical)
set_target_properties(Eqx_TPL_Wrapper_glfw_Typical PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
