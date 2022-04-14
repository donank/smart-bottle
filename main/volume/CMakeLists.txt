cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_SOURCE_DIR}/sensor)

project(volume VERSION 1.0.0 LANGUAGES CXX)
include(GNUInstallDirs)

add_compile_options(-Wall -Wconversion -Wextra -pedantic)

set(LIBSRC volume.cpp)
set(LIBINCLUDE volume.h)

add_library(volume
  SHARED
  ${LIBSRC}
  )

set_target_properties(volume PROPERTIES
  SOVERSION 1
  PUBLIC_HEADER "${LIBINCLUDE}")

target_link_libraries(volume sensor_static)

add_library(volume_static
  STATIC
  ${LIBSRC}
  )

set_target_properties(volume_static PROPERTIES
  PUBLIC_HEADER "${LIBINCLUDE}")

target_link_libraries(volume_static sensor_static)
