file(GLOB_RECURSE SOURCE_FILES
        "src/*.h"
        "src/*.cpp"
)

add_library(emu STATIC ${SOURCE_FILES})
target_include_directories(emu PRIVATE src/)
target_link_libraries(emu PRIVATE spdlog::spdlog)