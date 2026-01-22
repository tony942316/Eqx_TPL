cmake_minimum_required(VERSION 3.28)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG master)

FetchContent_MakeAvailable(glm)

FetchContent_GetProperties(
    glm
    SOURCE_DIR glm_source_dir)

add_library(Eqx_TPL_glm INTERFACE)
target_sources(Eqx_TPL_glm INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/glm.hpp)
target_include_directories(Eqx_TPL_glm INTERFACE ${glm_source_dir}/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../include/)

add_library(Eqx_TPL_glm_Typical INTERFACE)
target_sources(Eqx_TPL_glm_Typical INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/glm.hpp)
target_include_directories(Eqx_TPL_glm_Typical INTERFACE ${glm_source_dir}/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../include/)
target_link_libraries(Eqx_TPL_glm_Typical INTERFACE Eqx_Typical)
