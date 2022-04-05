cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../circularbuffer ${CMAKE_CURRENT_BINARY_DIR}/../circularbuffer)

project(Sensor VERSION 1.0.0 LANGUAGES CXX)
include(GNUInstallDirs)

add_compile_options(-Wall -Wconversion -Wextra -pedantic)

set(LIBSRC sensor.cpp)
set(LIBINCLUDE sensor.h)

add_library(sensor
  SHARED
  ${LIBSRC}
  )

set_target_properties(sensor PROPERTIES
  SOVERSION 1
  PUBLIC_HEADER "${LIBINCLUDE}")

target_link_libraries(sensor circularbuffer_static)

install(TARGETS sensor EXPORT ads1115rpi-targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})



add_library(sensor_static
  STATIC
  ${LIBSRC}
  )

set_target_properties(sensor_static PROPERTIES
  PUBLIC_HEADER "${LIBINCLUDE}")

target_link_libraries(sensor_static circularbuffer)

install(TARGETS sensor_static EXPORT ads1115rpi_static-targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
