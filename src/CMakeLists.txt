cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project( MagnifyingDevices )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(magnifier
  ImagesManager.h
  ImagesManager.cpp 
  main.cpp
)
target_link_libraries(magnifier ${OpenCV_LIBS})
