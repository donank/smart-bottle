cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_STANDARD 14)

#add_subdirectory("../circularbuffer" "../../build/sensor/circularbuffer")
include_directories(${CMAKE_SOURCE_DIR}/circularbuffer)
project(sensor VERSION 1.0.0 LANGUAGES CXX)
include(GNUInstallDirs)

add_compile_options(-Wall -Wconversion -Wextra -pedantic)

set(LIBSRC sensor.cpp)
set(LIBINCLUDE sensor.h)

message("sensor: CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
message("sensor: CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")
message("sensor: CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
message("sensor: CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}")

add_library(sensor
  SHARED
  ${LIBSRC}
  )

#set_target_properties(sensor PROPERTIES
#  SOVERSION 1
#  PUBLIC_HEADER "${LIBINCLUDE}")

target_link_libraries(sensor circularbuffer_static)

#install(TARGETS sensor EXPORT sensor-targets
#  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

add_library(sensor_static
  STATIC
  ${LIBSRC}
  )

#set_target_properties(sensor_static PROPERTIES
#  PUBLIC_HEADER "${LIBINCLUDE}")

target_link_libraries(sensor_static circularbuffer_static)

#install(TARGETS sensor_static EXPORT sensor_static-targets
#  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#target_include_directories(sensor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
