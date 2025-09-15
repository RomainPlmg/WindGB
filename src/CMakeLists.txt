# Add ARGPARSE
FetchContent_Declare(
        argparse
        GIT_REPOSITORY https://github.com/p-ranav/argparse.git
        GIT_TAG v3.2
)
# Add SFML
FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.1
)
FetchContent_MakeAvailable(argparse)
FetchContent_MakeAvailable(sfml)

add_executable(windgb
        main.cpp
)

target_link_libraries(windgb PRIVATE windgb_lib sfml-graphics argparse)