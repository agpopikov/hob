cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_STANDARD 99)
project(hob)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/bin)
set(CMAKE_CACHEFILE_DIR  ${PROJECT_SOURCE_DIR}/build/cache)

file(GLOB SOURCES ./src/*.h ./src/*.c)
add_library(hob ${SOURCES})
target_include_directories(hob PUBLIC ./src)

# Test stuff
enable_testing()
add_library(unity STATIC "lib/unity/src/unity.c")
target_include_directories(unity PUBLIC lib/unity/src)
add_executable(lib_test_app test/transport.c)
target_link_libraries(lib_test_app hob unity)
add_test(test build/bin/lib_test_app)
