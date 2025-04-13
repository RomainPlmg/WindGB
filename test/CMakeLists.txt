cmake_minimum_required(VERSION 3.20)
project(WindBG)

add_executable(CPU_Instructions
    cpu_instr.cpp
)

target_link_libraries(CPU_Instructions PRIVATE WindBG)
target_compile_definitions(CPU_Instructions PRIVATE TEST_DIR="${CMAKE_SOURCE_DIR}/libs/gb-test-roms/")

add_test(NAME CPU_Instr COMMAND CPU_Instructions)