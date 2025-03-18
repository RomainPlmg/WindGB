cmake_minimum_required(VERSION 3.20)
project(WindBG)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS OFF)

# Find OpenGL
set(OpenGL_GL_PREFERENCE "GLVND") # Target modern OpenGL
find_package(OpenGL REQUIRED)

# Compile submodules
add_subdirectory(libs/glfw)

# Recover all src files
file(GLOB_RECURSE SRC
        "src/*.h"
        "src/*.cpp"
)

add_executable(WindBG ${SRC})

# Add include directories
target_include_directories(WindBG PRIVATE
        "src/"
        "libs/glfw/include"
)

# Link libraries to the project
target_link_libraries(WindBG PRIVATE ${OPENGL_LIBRARY} glfw)

target_precompile_headers(WindBG PRIVATE "src/pch.h")