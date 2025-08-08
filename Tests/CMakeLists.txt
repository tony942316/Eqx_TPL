cmake_minimum_required(VERSION 3.28)

FetchContent_Declare(
    Eqx_Std
    GIT_REPOSITORY https://github.com/tony942316/Eqx_Std.git
    GIT_TAG main)

FetchContent_MakeAvailable(Eqx_Std)

add_subdirectory(Smoke/)
