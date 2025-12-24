project(MemoryPool)
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES Private/*.cpp)

add_library(MemoryPool STATIC ${SOURCES})

target_include_directories(MemoryPool PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Public)