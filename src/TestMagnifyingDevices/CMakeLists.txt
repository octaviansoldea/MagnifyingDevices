cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(MagnifyingDevices)
find_package( OpenCV REQUIRED )

add_executable(Magnifier main.cpp)
target_compile_features(Magnifier PRIVATE cxx_auto_type)

#find_package(libMagnifyingDevices REQUIRED)
target_link_libraries(Magnifier libMagnifyingDevices)
