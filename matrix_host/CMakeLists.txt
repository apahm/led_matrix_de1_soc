cmake_minimum_required(VERSION 3.10)

project(matrix_host)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set (CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "-Wall -Werror")

add_executable(matrix_host main.cpp mem_one_frame.cpp)

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

target_link_libraries( matrix_host ${OpenCV_LIBS} )


# QT

set (CMAKE_PREFIX_PATH "/home/alex/Qt/5.15.1/gcc_64")

find_package(Qt5 COMPONENTS REQUIRED Widgets Gui Core PrintSupport Network SerialPort)


target_link_libraries(matrix_host   
  Qt5::Widgets
  Qt5::Core
  Qt5::Gui
  Qt5::PrintSupport
  Qt5::Network
  Qt5::SerialPort)