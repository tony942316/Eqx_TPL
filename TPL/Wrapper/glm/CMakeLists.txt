# CMakeLists.txt

cmake_minimum_required(VERSION 3.28)

add_library(Eqx_TPL_Wrapper_glm STATIC)
target_sources(Eqx_TPL_Wrapper_glm PUBLIC
    FILE_SET CXX_MODULES FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/glm.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Mat4.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Vec3.cpp)
target_compile_features(Eqx_TPL_Wrapper_glm PUBLIC cxx_std_20)
target_link_libraries(Eqx_TPL_Wrapper_glm PRIVATE Eqx_Std Eqx_TPL_glm)
set_target_properties(Eqx_TPL_Wrapper_glm PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)

add_library(Eqx_TPL_Wrapper_glm_Typical STATIC)
target_sources(Eqx_TPL_Wrapper_glm_Typical PUBLIC
    FILE_SET CXX_MODULES FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/glm.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Mat4.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Vec3.cpp)
target_compile_features(Eqx_TPL_Wrapper_glm_Typical PUBLIC cxx_std_20)
target_link_libraries(Eqx_TPL_Wrapper_glm_Typical PRIVATE Eqx_Std_Typical
    Eqx_TPL_glm_Typical)
set_target_properties(Eqx_TPL_Wrapper_glm_Typical PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
