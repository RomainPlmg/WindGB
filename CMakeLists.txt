cmake_minimum_required(VERSION 3.20)
project(WindBG)

enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS OFF)

# Recover all src files
file(GLOB_RECURSE SRC
        "src/*.h"
        "src/*.cpp"
)

add_library(WindBG STATIC ${SRC})

# Add dependencies
set(SFML_BUILD_DOC OFF)
set(SFML_BUILD_EXAMPLES OFF)
set(SFML_USE_STATIC_STD_LIBS OFF)
add_subdirectory(libs/sfml)

# Add include directories
target_include_directories(WindBG PUBLIC
        "src/"
        "libs/sfml/include"
)

# Link libraries to the project
target_link_libraries(WindBG PRIVATE sfml-system sfml-graphics)

target_precompile_headers(WindBG PRIVATE "src/pch.h")

# Add test
add_subdirectory(test)
