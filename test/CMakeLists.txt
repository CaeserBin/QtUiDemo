set(CMAKE_CXX_STANDARD 23)
set(PROJECT_NAME "test")

# 递归查询本文件夹下所有源文件
file(GLOB_RECURSE SRC_FILES "*.cpp")

add_subdirectory(MemoryPool)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE MemoryPool)