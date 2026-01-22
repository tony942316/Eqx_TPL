# CMakeLists.txt

cmake_minimum_required(VERSION 3.28)

add_executable(Eqx_TPL_Tests_glad)
target_sources(Eqx_TPL_Tests_glad PRIVATE Main.cpp)
target_compile_features(Eqx_TPL_Tests_glad PRIVATE cxx_std_20)
set_target_properties(Eqx_TPL_Tests_glad PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
target_link_libraries(Eqx_TPL_Tests_glad PRIVATE Eqx_Std Eqx_TPL
    Eqx_TPL_Tests_Lib Eqx_Warnings_Error)

add_executable(Eqx_TPL_Tests_glad_Typical)
target_sources(Eqx_TPL_Tests_glad_Typical PRIVATE Main.cpp)
target_compile_features(Eqx_TPL_Tests_glad_Typical PRIVATE cxx_std_20)
set_target_properties(Eqx_TPL_Tests_glad_Typical PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
target_link_libraries(Eqx_TPL_Tests_glad_Typical PRIVATE Eqx_Std_Typical
    Eqx_TPL_Typical Eqx_TPL_Tests_Lib_Typical Eqx_Warnings_Error)

eqx_copy_asan(Eqx_TPL_Tests_glad_Typical)

add_test(NAME Eqx_TPL_Tests_glad
    COMMAND $<TARGET_FILE:Eqx_TPL_Tests_glad>)
add_test(NAME Eqx_TPL_Tests_glad_Typical
    COMMAND $<TARGET_FILE:Eqx_TPL_Tests_glad_Typical>)
