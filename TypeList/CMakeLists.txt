set(CMAKE_CXX_STANDARD 23)
set(PROJECT_NAME "TypeList")

# 递归查询本文件夹下所有源文件
file(GLOB_RECURSE SRC_FILES "*.cpp")

add_executable(${PROJECT_NAME} ${SRC_FILES})

include_directories(include)