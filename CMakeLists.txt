cmake_minimum_required(VERSION 3.28)

project(Eqx_TPL
    VERSION 0.2.0.0
    DESCRIPTION "Importable 3rd Party Libraries"
    HOMEPAGE_URL "https://github.com/tony942316/Eqx_TPL"
    LANGUAGES C CXX)

include(FetchContent)

add_subdirectory(TPL/)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    enable_testing()
    add_subdirectory(Tests/)
endif()
