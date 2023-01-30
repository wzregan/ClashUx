cmake_minimum_required(VERSION 3.2.4)
project(ClashUX)
set(EXECUTABLE_OUTPUT_PATH  /home/regan/code/Linux/ClashUX/bin)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(
        components components/lib src/inc
)

link_directories(lib)
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        StateMachine
        REQUIRED
        PATHS /home/regan/Qt/6.4.2/gcc_64/lib/cmake/Qt6
        )
set(QT_FRAMEWORK Qt::Core Qt::Gui Qt::Widgets Qt::StateMachine)
add_subdirectory(src)