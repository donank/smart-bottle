cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_SOURCE_DIR}/sensor)

project(temperature VERSION 1.0.0 LANGUAGES CXX)
include(GNUInstallDirs)

add_compile_options(-Wall -Wconversion -Wextra -pedantic)

set(LIBSRC temperature.cpp)
set(LIBINCLUDE temperature.h)

add_library(temperature
  SHARED
  ${LIBSRC}
  )

set_target_properties(temperature PROPERTIES
  SOVERSION 1
  PUBLIC_HEADER "${LIBINCLUDE}")

target_link_libraries(temperature sensor_static)

add_library(temperature_static
  STATIC
  ${LIBSRC}
  )

set_target_properties(temperature_static PROPERTIES
  PUBLIC_HEADER "${LIBINCLUDE}")

target_link_libraries(temperature_static sensor_static)
