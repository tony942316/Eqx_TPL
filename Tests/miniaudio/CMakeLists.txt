# CMakeLists.txt

cmake_minimum_required(VERSION 3.28)

add_executable(Eqx_TPL_Tests_miniaudio)
target_sources(Eqx_TPL_Tests_miniaudio PRIVATE Main.cpp)
target_compile_features(Eqx_TPL_Tests_miniaudio PRIVATE cxx_std_20)
set_target_properties(Eqx_TPL_Tests_miniaudio PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
target_link_libraries(Eqx_TPL_Tests_miniaudio PRIVATE Eqx_Std Eqx_TPL
    Eqx_Warnings_Error)

add_executable(Eqx_TPL_Tests_miniaudio_Typical)
target_sources(Eqx_TPL_Tests_miniaudio_Typical PRIVATE Main.cpp)
target_compile_features(Eqx_TPL_Tests_miniaudio_Typical PRIVATE cxx_std_20)
set_target_properties(Eqx_TPL_Tests_miniaudio_Typical PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
target_link_libraries(Eqx_TPL_Tests_miniaudio_Typical PRIVATE Eqx_Std_Typical
    Eqx_TPL_Typical Eqx_Warnings_Error)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Resources/Sounds/)
configure_file(
    ${CMAKE_SOURCE_DIR}/Resources/Sounds/Mario_Coin.mp3
    ${CMAKE_CURRENT_BINARY_DIR}/Resources/Sounds/Mario_Coin.mp3
    COPYONLY)

eqx_copy_asan(Eqx_TPL_Tests_miniaudio_Typical)

add_test(NAME Eqx_TPL_Tests_miniaudio
    COMMAND $<TARGET_FILE:Eqx_TPL_Tests_miniaudio>)
add_test(NAME Eqx_TPL_Tests_miniaudio_Typical
    COMMAND $<TARGET_FILE:Eqx_TPL_Tests_miniaudio_Typical>)
