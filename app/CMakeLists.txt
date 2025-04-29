set(SOURCE_FILES src/main.cpp)

add_executable(emuapp ${SOURCE_FILES})

target_include_directories(emuapp PRIVATE ${CMAKE_SOURCE_DIR}/emu/src)
target_link_libraries(emuapp PRIVATE emu)