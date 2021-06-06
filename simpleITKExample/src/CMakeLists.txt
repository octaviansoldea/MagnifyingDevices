set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(HelloWorld)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})
  
add_executable(HelloWorld HelloWorld.cxx)

message(STATUS "ITK_LIBRARIES = ${ITK_LIBRARIES}")

find_library(COREFOUNDATION_LIBRARY CoreFoundation )

target_link_libraries(HelloWorld ${ITK_LIBRARIES}
${COREFOUNDATION_LIBRARY}
libitkgdcmjpeg12-5.1.a
libitkgdcmuuid-5.1.a
libitkgdcmjpeg16-5.1.a
libitkgdcmCommon-5.1.a
libitkgdcmopenjp2-5.1.a
libitkgdcmDSED-5.1.a
libitkgdcmjpeg8-5.1.a
libitkgdcmcharls-5.1.a
libitkgdcmIOD-5.1.a
)
