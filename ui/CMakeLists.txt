set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        OpenGL
        OpenGLWidgets
        REQUIRED)

# 修正 GLOB 命令语法，移除无效的点号
file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE HEADER_FILES *.h *.hpp)

add_library(Ui STATIC ${SOURCE_FILES})

target_link_libraries(Ui PUBLIC
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::OpenGL
        Qt6::OpenGLWidgets
)

target_include_directories(Ui PUBLIC .)
target_include_directories(Ui PRIVATE GLWidget)
target_include_directories(Ui PRIVATE
        $<TARGET_PROPERTY:Ui,INTERFACE_INCLUDE_DIRECTORIES>
        ${CMAKE_CURRENT_BINARY_DIR}/Ui_autogen/include
)