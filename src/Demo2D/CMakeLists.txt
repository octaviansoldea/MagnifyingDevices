cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(Demo2D)
find_package( OpenCV REQUIRED )

include_directories(
    ${OpenCV_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/libMagnifyingDevices/
)

add_executable(Demo2D main.cpp)
#target_compile_features(Demo2D PRIVATE cxx_auto_type)

find_library(COREFOUNDATION_LIBRARY CoreFoundation)

target_link_libraries(Demo2D
  libMagnifyingDevices
  ${MACOSX_LIBRARIES}
)
