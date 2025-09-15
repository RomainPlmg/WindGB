# Add SPDLOG
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.15.3
)
FetchContent_MakeAvailable(spdlog)

file(GLOB_RECURSE SRC
        "*.cpp"
        "*.hpp"
)

add_library(windgb_lib ${SRC})

target_link_libraries(windgb_lib PUBLIC spdlog::spdlog)
target_include_directories(windgb_lib PUBLIC .)
target_compile_definitions(windgb_lib PUBLIC PROJECT_SRC="${CMAKE_SOURCE_DIR}")