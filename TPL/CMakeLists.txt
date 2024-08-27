cmake_minimum_required(VERSION 3.28)

add_library(Eqx_TPL_GMF INTERFACE)

target_compile_options(Eqx_TPL_GMF INTERFACE --relocatable-pch
    -fretain-comments-from-system-headers)

add_subdirectory(include/Eqx/TPL/stb)

add_library(Eqx_TPL INTERFACE)
target_include_directories(Eqx_TPL INTERFACE include)
target_link_libraries(Eqx_TPL INTERFACE Eqx_Stb Eqx_TPL_GMF)
