cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_C_STANDARD 99)
project(hob LANGUAGES C)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/bin)

file(GLOB SOURCE_HEADERS ./src/*.h)
file(GLOB SOURCES ./src/*.c)
add_library(hob ${SOURCE_HEADERS} ${SOURCES})
set_target_properties(hob PROPERTIES LINKER_LANGUAGE C)
target_include_directories(hob PUBLIC ./src)

# Test stuff
enable_testing()
add_library(unity STATIC "lib/unity/src/unity.c")
target_include_directories(unity PUBLIC lib/unity/src)
add_executable(lib_test_app test/transport_test.c)
target_link_libraries(lib_test_app hob unity)
add_test(test build/bin/lib_test_app)
