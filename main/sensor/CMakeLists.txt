cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_STANDARD 14)

#add_subdirectory("../circularbuffer" circularbuffer)
include_directories(${CMAKE_SOURCE_DIR}/circularbuffer)
find_package (Threads)

project(sensor VERSION 1.0.0 LANGUAGES CXX)
include(GNUInstallDirs)

add_compile_options(-Wall -Wconversion -Wextra -pedantic)

set(LIBSRC sensor.cpp)
set(LIBINCLUDE sensor.h)

add_library(sensor
  SHARED
  ${LIBSRC}
  )

target_link_libraries(sensor circularbuffer_static)

add_library(sensor_static
  STATIC
  ${LIBSRC}
  )

target_link_libraries(sensor_static circularbuffer_static)

