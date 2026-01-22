# CMakeLists.txt

cmake_minimum_required(VERSION 3.28)

add_executable(Eqx_TPL_Tests_freetype)
target_sources(Eqx_TPL_Tests_freetype PRIVATE Main.cpp)
target_compile_features(Eqx_TPL_Tests_freetype PRIVATE cxx_std_20)
set_target_properties(Eqx_TPL_Tests_freetype PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
target_link_libraries(Eqx_TPL_Tests_freetype PRIVATE Eqx_Std Eqx_TPL
    Eqx_TPL_Tests_Lib Eqx_Warnings_Error)

add_executable(Eqx_TPL_Tests_freetype_Typical)
target_sources(Eqx_TPL_Tests_freetype_Typical PRIVATE Main.cpp)
target_compile_features(Eqx_TPL_Tests_freetype_Typical PRIVATE cxx_std_20)
set_target_properties(Eqx_TPL_Tests_freetype_Typical PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
target_link_libraries(Eqx_TPL_Tests_freetype_Typical PRIVATE Eqx_Std_Typical
    Eqx_TPL_Typical Eqx_TPL_Tests_Lib_Typical Eqx_Warnings_Error)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Resources/Fonts/)
configure_file(
    ${CMAKE_SOURCE_DIR}/Resources/Fonts/Hack-Regular.ttf
    ${CMAKE_CURRENT_BINARY_DIR}/Resources/Fonts/Hack-Regular.ttf
    COPYONLY)

eqx_copy_asan(Eqx_TPL_Tests_freetype_Typical)

add_test(NAME Eqx_TPL_Tests_freetype
    COMMAND $<TARGET_FILE:Eqx_TPL_Tests_freetype>)
add_test(NAME Eqx_TPL_Tests_freetype_Typical
    COMMAND $<TARGET_FILE:Eqx_TPL_Tests_freetype_Typical>)
