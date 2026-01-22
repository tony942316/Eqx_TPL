# Explore.cmake

add_library(Eqx_TPL_Tests_Explore STATIC)
target_sources(Eqx_TPL_Tests_Explore PUBLIC
    FILE_SET CXX_MODULES FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/Explore.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Glad.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Stb_Image.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Glm.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Glm_Image.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Freetype.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Glm_Freetype.cpp)
target_compile_features(Eqx_TPL_Tests_Explore PUBLIC cxx_std_20)
target_link_libraries(Eqx_TPL_Tests_Explore PRIVATE Eqx_Std Eqx_TPL
    Eqx_TPL_Tests_Lib)
set_target_properties(Eqx_TPL_Tests_Explore PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)

add_library(Eqx_TPL_Tests_Explore_Typical STATIC)
target_sources(Eqx_TPL_Tests_Explore_Typical PUBLIC
    FILE_SET CXX_MODULES FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/Explore.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Glad.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Stb_Image.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Glm.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Glm_Image.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Freetype.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Glm_Freetype.cpp)
target_compile_features(Eqx_TPL_Tests_Explore_Typical PUBLIC cxx_std_20)
target_link_libraries(Eqx_TPL_Tests_Explore_Typical PRIVATE Eqx_Std_Typical
    Eqx_TPL_Typical Eqx_TPL_Tests_Lib_Typical)
set_target_properties(Eqx_TPL_Tests_Explore_Typical PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
