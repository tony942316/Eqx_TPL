cmake_minimum_required(VERSION 3.28)

add_executable(Test_stb_image_Smoke)
target_sources(Test_stb_image_Smoke PRIVATE Main.cpp)
target_compile_features(Test_stb_image_Smoke PRIVATE cxx_std_20)
target_compile_definitions(Test_stb_image_Smoke PRIVATE EQX_SMOKE)
set_target_properties(Test_stb_image_Smoke PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
target_link_libraries(Test_stb_image_Smoke PRIVATE Eqx_Std Eqx_TPL
    Eqx_Warnings_Error)

add_executable(Test_stb_image_Explore)
target_sources(Test_stb_image_Explore PRIVATE Main.cpp)
target_compile_features(Test_stb_image_Explore PRIVATE cxx_std_20)
set_target_properties(Test_stb_image_Explore PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
target_link_libraries(Test_stb_image_Explore PRIVATE Eqx_Std Eqx_TPL
    Eqx_Warnings_Error)

add_executable(Test_stb_image_Smoke_Typical)
target_sources(Test_stb_image_Smoke_Typical PRIVATE Main.cpp)
target_compile_features(Test_stb_image_Smoke_Typical PRIVATE cxx_std_20)
target_compile_definitions(Test_stb_image_Smoke_Typical PRIVATE EQX_SMOKE)
set_target_properties(Test_stb_image_Smoke_Typical PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
target_link_libraries(Test_stb_image_Smoke_Typical PRIVATE Eqx_Std_Typical
    Eqx_TPL_Typical Eqx_Warnings_Error)

add_executable(Test_stb_image_Explore_Typical)
target_sources(Test_stb_image_Explore_Typical PRIVATE Main.cpp)
target_compile_features(Test_stb_image_Explore_Typical PRIVATE cxx_std_20)
set_target_properties(Test_stb_image_Explore_Typical PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
target_link_libraries(Test_stb_image_Explore_Typical PRIVATE Eqx_Std_Typical
    Eqx_TPL_Typical Eqx_Warnings_Error)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Resources/Textures/)
configure_file(
    ${CMAKE_SOURCE_DIR}/Resources/Textures/BrickWall.png
    ${CMAKE_CURRENT_BINARY_DIR}/Resources/Textures/BrickWall.png
    COPYONLY)

eqx_copy_asan(Test_stb_image_Smoke_Typical)
eqx_copy_asan(Test_stb_image_Explore_Typical)

add_test(NAME stb_image_Smoke
    COMMAND $<TARGET_FILE:Test_stb_image_Smoke>)
add_test(NAME stb_image_Smoke_Typical
    COMMAND $<TARGET_FILE:Test_stb_image_Smoke_Typical>)
