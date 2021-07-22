cmake_minimum_required(VERSION 3.10)

project(matrix_host LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 11)

add_executable(matrix_host main.cpp mem_one_frame.cpp)

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

target_link_libraries( matrix_host ${OpenCV_LIBS} )