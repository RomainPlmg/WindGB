file(GLOB_RECURSE SOURCE_FILES
        "src/*.h"
        "src/*.cpp"
)

add_executable(emuapp ${SOURCE_FILES})

target_include_directories(emuapp PRIVATE ${CMAKE_SOURCE_DIR}/emu/src)
target_link_libraries(emuapp PRIVATE emu argparse SFML::Graphics)