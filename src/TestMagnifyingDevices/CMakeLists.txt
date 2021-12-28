cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(MagnifyingDevices)
find_package( OpenCV REQUIRED )

include_directories(
    ${OpenCV_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/libMagnifyingDevices/
)

add_executable(MagnifyingDevices main.cpp)
#target_compile_features(MagnifyingDevices PRIVATE cxx_auto_type)

find_library(COREFOUNDATION_LIBRARY CoreFoundation )

target_link_libraries(MagnifyingDevices
    libMagnifyingDevices
    ${COREFOUNDATION_LIBRARY}
)

add_test(TestMagnifyingDevices0 MagnifyingDevices 0)
add_test(TestMagnifyingDevices1 MagnifyingDevices 1)
