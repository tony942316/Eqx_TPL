cmake_minimum_required(VERSION 3.28)

add_executable(Test_glm_Smoke)
target_sources(Test_glm_Smoke PRIVATE Main.cpp)
target_compile_features(Test_glm_Smoke PRIVATE cxx_std_20)
target_compile_definitions(Test_glm_Smoke PRIVATE EQX_SMOKE)
set_target_properties(Test_glm_Smoke PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
target_link_libraries(Test_glm_Smoke PRIVATE Eqx_Std Eqx_TPL)

add_executable(Test_glm_Explore)
target_sources(Test_glm_Explore PRIVATE Main.cpp)
target_compile_features(Test_glm_Explore PRIVATE cxx_std_20)
set_target_properties(Test_glm_Explore PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
target_link_libraries(Test_glm_Explore PRIVATE Eqx_Std Eqx_TPL)

add_executable(Test_glm_Smoke_Typical)
target_sources(Test_glm_Smoke_Typical PRIVATE Main.cpp)
target_compile_features(Test_glm_Smoke_Typical PRIVATE cxx_std_20)
target_compile_definitions(Test_glm_Smoke_Typical PRIVATE EQX_SMOKE)
set_target_properties(Test_glm_Smoke_Typical PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
target_link_libraries(Test_glm_Smoke_Typical PRIVATE Eqx_Std_Typical
    Eqx_TPL_Typical)

add_executable(Test_glm_Explore_Typical)
target_sources(Test_glm_Explore_Typical PRIVATE Main.cpp)
target_compile_features(Test_glm_Explore_Typical PRIVATE cxx_std_20)
set_target_properties(Test_glm_Explore_Typical PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
target_link_libraries(Test_glm_Explore_Typical PRIVATE Eqx_Std_Typical
    Eqx_TPL_Typical)

eqx_copy_asan(Test_glm_Smoke_Typical)
eqx_copy_asan(Test_glm_Explore_Typical)

add_test(NAME glm_Smoke
    COMMAND $<TARGET_FILE:Test_glm_Smoke>)
add_test(NAME glm_Smoke_Typical
    COMMAND $<TARGET_FILE:Test_glm_Smoke_Typical>)
