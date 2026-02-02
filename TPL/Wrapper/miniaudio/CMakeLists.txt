# CMakeLists.txt

cmake_minimum_required(VERSION 3.28)

add_library(Eqx_TPL_Wrapper_miniaudio STATIC)
target_sources(Eqx_TPL_Wrapper_miniaudio PUBLIC
    FILE_SET CXX_MODULES FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/miniaudio.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Sound.cpp)
target_compile_features(Eqx_TPL_Wrapper_miniaudio PUBLIC cxx_std_20)
target_link_libraries(Eqx_TPL_Wrapper_miniaudio PRIVATE Eqx_Std
    Eqx_TPL_miniaudio Eqx_TPL_glad)
set_target_properties(Eqx_TPL_Wrapper_miniaudio PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)

add_library(Eqx_TPL_Wrapper_miniaudio_Typical STATIC)
target_sources(Eqx_TPL_Wrapper_miniaudio_Typical PUBLIC
    FILE_SET CXX_MODULES FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/miniaudio.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Sound.cpp)
target_compile_features(Eqx_TPL_Wrapper_miniaudio_Typical PUBLIC cxx_std_20)
target_link_libraries(Eqx_TPL_Wrapper_miniaudio_Typical PRIVATE Eqx_Std_Typical
    Eqx_TPL_miniaudio_Typical Eqx_TPL_glad_Typical)
set_target_properties(Eqx_TPL_Wrapper_miniaudio_Typical PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
