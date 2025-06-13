cmake_minimum_required(VERSION 3.29)
project(untitled)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


set(CMAKE_PREFIX_PATH "D:/Qt/5.15.2/msvc2019_64")#告诉 CMake 在该路径下查找 Qt 库和其他依赖项。
# 设置源码与执行时字符集为 UTF-8（GCC/Clang）
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -finput-charset=UTF-8 -fexec-charset=UTF-8")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finput-charset=UTF-8 -fexec-charset=UTF-8")

# 针对 MSVC 设置 UTF-8 源码处理
if(MSVC)
    add_compile_options(/utf-8)
endif()

# 引入自定义的 .cmake 文件,用于自动复制dll
include(${PROJECT_SOURCE_DIR}/cmake/QtRuntimeUtils.cmake)
set(MyUIForms  ${PROJECT_SOURCE_DIR}/Sources/Forms)
set(MyUIHeaders ${PROJECT_SOURCE_DIR}/Sources/Headers)
include_directories(
        ${PROJECT_SOURCE_DIR}/Sources/Headers
)

find_package(Qt5 COMPONENTS
        Multimedia
        Core
        Gui
        Widgets
        REQUIRED)



add_executable(main
        WIN32 #该可执行文件是为 Windows 平台构建的 GUI 应用程序（不带控制台窗口
        Sources/main.cpp
        ${MyUIForms}/Mainwindows.cpp
        ${MyUIForms}/Mainwindows.ui
        ${MyUIHeaders}/Mainwindows.h
        ${MyUIForms}/Taskdialog.cpp
        ${MyUIForms}/Taskdialog.ui
        ${MyUIHeaders}/Taskdialog.h
        ${MyUIForms}/add.cpp
        ${MyUIForms}/add.ui
        ${MyUIHeaders}/add.h
)




target_link_libraries(main
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Multimedia
)

configure_qt_runtime(main)
