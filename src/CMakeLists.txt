cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(MagnifyingDevices)

find_package(OpenCV REQUIRED)

add_subdirectory (libMagnifyingDevices)
add_subdirectory (TestMagnifyingDevices)

