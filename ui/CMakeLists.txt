set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

# 修正 GLOB 命令语法，移除无效的点号
file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE HEADER_FILES *.h *.hpp)

add_library(Ui STATIC ${SOURCE_FILES})

target_link_libraries(Ui PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

# 在 CMakeLists.txt 中设置 Qt 静态链接
set(Qt5_DIR "C:/Qt/Qt5.14.2/5.14.2/mingw73_64/lib/cmake")

target_include_directories(Ui PUBLIC .)
target_include_directories(Ui PRIVATE GLWidget)
target_include_directories(Ui PRIVATE
        $<TARGET_PROPERTY:Ui,INTERFACE_INCLUDE_DIRECTORIES>
        ${CMAKE_CURRENT_BINARY_DIR}/Ui_autogen/include
)