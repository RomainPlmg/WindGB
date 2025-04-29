file(GLOB_RECURSE SOURCE_FILES
        "src/*.h"
        "src/*.cpp"
)

add_library(emu STATIC ${SOURCE_FILES})

add_subdirectory(libs/spdlog)
add_subdirectory(libs/argparse)

target_link_libraries(emu PRIVATE spdlog::spdlog argparse)