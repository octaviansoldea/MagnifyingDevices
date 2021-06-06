cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(MagnifyingDevices)
find_package( OpenCV REQUIRED )
find_package( ITK REQUIRED )

include_directories(${OpenCV_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/libMagnifyingDevices/include
)
include(${ITK_USE_FILE})
#include_directories(${ITK_INCLUDE_DIRS})

link_directories(/Users/octavian/Octavian/Programs/ITK/build_itk_5.1.2/lib/)
add_executable(Magnifier main.cpp)
target_compile_features(Magnifier PRIVATE cxx_auto_type)

#find_package(libMagnifyingDevices REQUIRED)
#target_link_libraries(Magnifier PUBLIC libMagnifyingDevices ${ITK_LIBRARIES})
find_library(COREFOUNDATION_LIBRARY CoreFoundation )


target_link_libraries(Magnifier 
libMagnifyingDevices
${ITK_LIBRARIES}
${COREFOUNDATION_LIBRARY}
itkgdcmjpeg12-5.1
itkgdcmuuid-5.1
itkgdcmjpeg16-5.1
itkgdcmCommon-5.1
itkgdcmopenjp2-5.1
itkgdcmDSED-5.1
itkgdcmjpeg8-5.1
itkgdcmcharls-5.1
itkgdcmIOD-5.1
)
