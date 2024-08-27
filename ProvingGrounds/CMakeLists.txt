cmake_minimum_required(VERSION 3.28)

message("Compiler is: ${CMAKE_CXX_COMPILER_ID}")

add_executable(ProvingGrounds)
target_sources(ProvingGrounds PRIVATE Main.cpp)
target_compile_features(ProvingGrounds PRIVATE cxx_std_20)
set_target_properties(ProvingGrounds PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
