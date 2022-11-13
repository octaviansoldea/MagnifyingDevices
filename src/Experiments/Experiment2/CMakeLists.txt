cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(Experiment2)
find_package( OpenCV REQUIRED )

find_library(COREFOUNDATION_LIBRARY CoreFoundation)

find_package(VTK COMPONENTS
  CommonColor
  CommonCore
  CommonDataModel
  CommonTransforms
  FiltersSources
  IOImage
  InteractionStyle
  RenderingAnnotation
  RenderingContextOpenGL2
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingOpenGL2
)

if (NOT VTK_FOUND)
  message(FATAL_ERROR "Axes: Unable to find the VTK build folder.")
endif()


include_directories(
    ${OpenCV_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/libMagnifyingDevices/
    ${VTK_INCLUDE_DIRS}
)

# Prevent a "command line is too long" failure in Windows.
set(CMAKE_NINJA_FORCE_RESPONSE_FILE "ON" CACHE BOOL "Force Ninja to use response files.")


add_executable(Experiment2 main.cpp)

target_link_libraries(Experiment2
  PUBLIC
  libMagnifyingDevices
  ${COREFOUNDATION_LIBRARY}
  ${VTK_LIBRARIES}
)


