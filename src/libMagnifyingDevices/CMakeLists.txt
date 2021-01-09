cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

project(libMagnifyingDevices)
add_library(libMagnifyingDevices
  include/ImagesManager.h
  src/ImagesManager.cpp
)

target_include_directories(libMagnifyingDevices
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_compile_features(libMagnifyingDevices PRIVATE cxx_auto_type)

target_link_libraries(libMagnifyingDevices
    PUBLIC
        ${OpenCV_LIBS}
)
#[==[
include(GNUInstallDirs)

set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/libMagnifyingDevices)

install(TARGETS libMagnifyingDevices
    EXPORT libMagnifyingDevices-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#Export the targets to a script
install(EXPORT libMagnifyingDevices-targets
    FILE
      libMagnifyingDevicesTargets.cmake
    NAMESPACE
      libMagnifyingDevices
    DESTINATION
        ${INSTALL_CONFIGDIR}
)

#Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
#write_basic_package_version_file(
#    ${CMAKE_CURRENT_BINARY_DIR}/libMagnifyingDevicesConfigVersion.cmake
#    VERSION ${PROJECT_VERSION}
#    COMPATIBILITY AnyNewerVersion
#)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/libMagnifyingDevicesConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/libMagnifyingDevicesConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

#Install the config, configversion and custom find modules
install(FILES
    #${CMAKE_CURRENT_LIST_DIR}/cmake/FindRapidJSON.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/libMagnifyingDevicesConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/libMagnifyingDevicesConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

#configure_file(${CMAKE_CURRENT_LIST_DIR}/cmake/FindRapidJSON.cmake
#    ${CMAKE_CURRENT_BINARY_DIR}/FindRapidJSON.cmake
#    COPYONLY)

export(EXPORT libMagnifyingDevices-targets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/libMagnifyingDevicesTargets.cmake
    NAMESPACE libMagnifyingDevices::)

#Register package in user's package registry
export(PACKAGE libMagnifyingDevices)

]==]
