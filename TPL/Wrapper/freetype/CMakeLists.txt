# CMakeLists.txt

cmake_minimum_required(VERSION 3.28)

add_library(Eqx_TPL_Wrapper_freetype STATIC)
target_sources(Eqx_TPL_Wrapper_freetype PUBLIC
    FILE_SET CXX_MODULES FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/freetype.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FT_Library.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FT_Face.cpp)
target_compile_features(Eqx_TPL_Wrapper_freetype PUBLIC cxx_std_20)
target_link_libraries(Eqx_TPL_Wrapper_freetype PRIVATE Eqx_Std Eqx_TPL_freetype)
set_target_properties(Eqx_TPL_Wrapper_freetype PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)

add_library(Eqx_TPL_Wrapper_freetype_Typical STATIC)
target_sources(Eqx_TPL_Wrapper_freetype_Typical PUBLIC
    FILE_SET CXX_MODULES FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/freetype.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FT_Library.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FT_Face.cpp)
target_compile_features(Eqx_TPL_Wrapper_freetype_Typical PUBLIC cxx_std_20)
target_link_libraries(Eqx_TPL_Wrapper_freetype_Typical PRIVATE Eqx_Std_Typical
    Eqx_TPL_freetype_Typical)
set_target_properties(Eqx_TPL_Wrapper_freetype_Typical PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
