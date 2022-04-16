cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_STANDARD 14)

#add_subdirectory("../sensor" "../../build/sensor")
#include(../sensor/CMakeLists.txt)
include_directories(${CMAKE_SOURCE_DIR}/sensor)

project(ph VERSION 1.0.0 LANGUAGES CXX)
include(GNUInstallDirs)

add_compile_options(-Wall -Wconversion -Wextra -pedantic)

set(LIBSRC ph.cpp)
set(LIBINCLUDE ph.h)

add_library(ph
  SHARED
  ${LIBSRC}
  )

target_link_libraries(ph PRIVATE sensor_static)

add_library(ph_static
  STATIC
  ${LIBSRC}
  )

target_link_libraries(ph_static PRIVATE sensor_static)
