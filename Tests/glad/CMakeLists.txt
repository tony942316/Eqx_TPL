cmake_minimum_required(VERSION 3.28)

add_executable(Test_glad_Smoke)
target_sources(Test_glad_Smoke PRIVATE Main.cpp)
target_compile_features(Test_glad_Smoke PRIVATE cxx_std_20)
target_compile_definitions(Test_glad_Smoke PRIVATE EQX_SMOKE)
set_target_properties(Test_glad_Smoke PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
target_link_libraries(Test_glad_Smoke PRIVATE Eqx_Std Eqx_TPL
    Eqx_Warnings_Error)

add_executable(Test_glad_Explore)
target_sources(Test_glad_Explore PRIVATE Main.cpp)
target_compile_features(Test_glad_Explore PRIVATE cxx_std_20)
set_target_properties(Test_glad_Explore PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
target_link_libraries(Test_glad_Explore PRIVATE Eqx_Std Eqx_TPL
    Eqx_Warnings_Error)

add_executable(Test_glad_Smoke_Typical)
target_sources(Test_glad_Smoke_Typical PRIVATE Main.cpp)
target_compile_features(Test_glad_Smoke_Typical PRIVATE cxx_std_20)
target_compile_definitions(Test_glad_Smoke_Typical PRIVATE EQX_SMOKE)
set_target_properties(Test_glad_Smoke_Typical PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
target_link_libraries(Test_glad_Smoke_Typical PRIVATE Eqx_Std_Typical
    Eqx_TPL_Typical Eqx_Warnings_Error)

add_executable(Test_glad_Explore_Typical)
target_sources(Test_glad_Explore_Typical PRIVATE Main.cpp)
target_compile_features(Test_glad_Explore_Typical PRIVATE cxx_std_20)
set_target_properties(Test_glad_Explore_Typical PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
target_link_libraries(Test_glad_Explore_Typical PRIVATE Eqx_Std_Typical
    Eqx_TPL_Typical Eqx_Warnings_Error)

eqx_copy_asan(Test_glad_Smoke_Typical)
eqx_copy_asan(Test_glad_Explore_Typical)

add_test(NAME glad_Smoke
    COMMAND $<TARGET_FILE:Test_glad_Smoke>)
add_test(NAME glad_Smoke_Typical
    COMMAND $<TARGET_FILE:Test_glad_Smoke_Typical>)
