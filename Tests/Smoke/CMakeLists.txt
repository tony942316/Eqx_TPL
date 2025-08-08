cmake_minimum_required(VERSION 3.28)

add_executable(Smoke)
target_sources(Smoke PRIVATE Smoke.cpp)
target_compile_features(Smoke PRIVATE cxx_std_20)
set_target_properties(Smoke PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
target_link_libraries(Smoke PRIVATE Eqx_Std Eqx_TPL)
