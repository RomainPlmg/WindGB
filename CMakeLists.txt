cmake_minimum_required(VERSION 3.20)
project(WindGB)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(libs/spdlog)
add_subdirectory(libs/argparse)
add_subdirectory(libs/sfml)

add_subdirectory(emu)
add_subdirectory(app)