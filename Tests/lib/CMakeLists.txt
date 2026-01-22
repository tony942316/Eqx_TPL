# CMakeLists.txt

cmake_minimum_required(VERSION 3.28)

add_library(Eqx_TPL_Tests_Lib STATIC)
target_sources(Eqx_TPL_Tests_Lib PUBLIC
    FILE_SET CXX_MODULES FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/Frame_Timer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Lib.cpp)
target_compile_features(Eqx_TPL_Tests_Lib PUBLIC cxx_std_20)
target_link_libraries(Eqx_TPL_Tests_Lib PRIVATE Eqx_Std)
set_target_properties(Eqx_TPL_Tests_Lib PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)

add_library(Eqx_TPL_Tests_Lib_Typical STATIC)
target_sources(Eqx_TPL_Tests_Lib_Typical PUBLIC
    FILE_SET CXX_MODULES FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/Frame_Timer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Lib.cpp)
target_compile_features(Eqx_TPL_Tests_Lib_Typical PUBLIC cxx_std_20)
target_link_libraries(Eqx_TPL_Tests_Lib_Typical PRIVATE Eqx_Std_Typical)
set_target_properties(Eqx_TPL_Tests_Lib_Typical PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
