# CMakeLists.txt

cmake_minimum_required(VERSION 3.28)

add_library(Eqx_TPL_Wrapper_glad STATIC)
target_sources(Eqx_TPL_Wrapper_glad PUBLIC
    FILE_SET CXX_MODULES FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/glad.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Texture.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Context.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Buffer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Vertex_Array.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Shader_Source.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Shader_Program.cpp)
target_compile_features(Eqx_TPL_Wrapper_glad PUBLIC cxx_std_20)
target_link_libraries(Eqx_TPL_Wrapper_glad PRIVATE Eqx_Std Eqx_TPL_glad)
set_target_properties(Eqx_TPL_Wrapper_glad PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)

add_library(Eqx_TPL_Wrapper_glad_Typical STATIC)
target_sources(Eqx_TPL_Wrapper_glad_Typical PUBLIC
    FILE_SET CXX_MODULES FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/glad.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Texture.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Context.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Buffer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Vertex_Array.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Shader_Source.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Shader_Program.cpp)
target_compile_features(Eqx_TPL_Wrapper_glad_Typical PUBLIC cxx_std_20)
target_link_libraries(Eqx_TPL_Wrapper_glad_Typical PRIVATE Eqx_Std_Typical
    Eqx_TPL_glad_Typical)
set_target_properties(Eqx_TPL_Wrapper_glad_Typical PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
