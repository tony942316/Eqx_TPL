cmake_minimum_required(VERSION 3.28)

add_executable(Test_stb_image_Smoke)
target_sources(Test_stb_image_Smoke PRIVATE Smoke.cpp)
target_compile_features(Test_stb_image_Smoke PRIVATE cxx_std_20)
set_target_properties(Test_stb_image_Smoke PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
target_link_libraries(Test_stb_image_Smoke PRIVATE Eqx_Std Eqx_TPL)

add_executable(Test_stb_image_Explore)
target_sources(Test_stb_image_Explore PRIVATE Explore.cpp)
target_compile_features(Test_stb_image_Explore PRIVATE cxx_std_20)
set_target_properties(Test_stb_image_Explore PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
target_link_libraries(Test_stb_image_Explore PRIVATE Eqx_Std Eqx_TPL)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Resources/Textures/)
configure_file(
    ${CMAKE_SOURCE_DIR}/Resources/Textures/BrickWall.png
    ${CMAKE_CURRENT_BINARY_DIR}/Resources/Textures/BrickWall.png
    COPYONLY)

if (Eqx_MSVC)
    add_custom_command(TARGET Test_stb_image_Smoke POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/clang_rt.asan_dynamic-x86_64.dll
            $<TARGET_FILE_DIR:Test_stb_image_Smoke>)
elseif (Eqx_Clang OR Eqx_GNU)

else()
    message(FATAL_ERROR "Invalid Configuration!")
endif()

add_test(NAME stb_image_Smoke
    COMMAND $<TARGET_FILE:Test_stb_image_Smoke>)

