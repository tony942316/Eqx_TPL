cmake_minimum_required(VERSION 3.28)

project(Eqx_TPL
    VERSION 0.1.0
    DESCRIPTION "Importable 3rd Party Libraries"
    LANGUAGES C CXX)

include(FetchContent)

add_subdirectory(TPL)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_subdirectory(ProvingGrounds)
endif()
