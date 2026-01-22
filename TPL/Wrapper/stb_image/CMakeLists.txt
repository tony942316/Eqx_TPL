# CMakeLists.txt

cmake_minimum_required(VERSION 3.28)

add_library(Eqx_TPL_Wrapper_stb_image STATIC)
target_sources(Eqx_TPL_Wrapper_stb_image PUBLIC
    FILE_SET CXX_MODULES FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/stb_image.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Image.cpp)
target_compile_features(Eqx_TPL_Wrapper_stb_image PUBLIC cxx_std_20)
target_link_libraries(Eqx_TPL_Wrapper_stb_image PRIVATE Eqx_Std
    Eqx_TPL_stb)
set_target_properties(Eqx_TPL_Wrapper_stb_image PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)

add_library(Eqx_TPL_Wrapper_stb_image_Typical STATIC)
target_sources(Eqx_TPL_Wrapper_stb_image_Typical PUBLIC
    FILE_SET CXX_MODULES FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/stb_image.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Image.cpp)
target_compile_features(Eqx_TPL_Wrapper_stb_image_Typical PUBLIC cxx_std_20)
target_link_libraries(Eqx_TPL_Wrapper_stb_image_Typical PRIVATE Eqx_Std_Typical
    Eqx_TPL_stb_Typical)
set_target_properties(Eqx_TPL_Wrapper_stb_image_Typical PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
