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
set(pathPh "../../ph/sensor")
message("ph relative path: ${pathPh}")
message("ph: CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
message("ph: CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")
message("ph: CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
message("ph: CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}")

add_library(ph
  SHARED
  ${LIBSRC}
  )

#set_target_properties(ph PROPERTIES
#  SOVERSION 1
#  PUBLIC_HEADER "${LIBINCLUDE}")

target_link_libraries(ph PRIVATE sensor_static)

#install(TARGETS ph EXPORT ph-targets
#  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})



add_library(ph_static
  STATIC
  ${LIBSRC}
  )

#set_target_properties(ph_static PROPERTIES
#  PUBLIC_HEADER "${LIBINCLUDE}")

target_link_libraries(ph_static PRIVATE sensor_static)

#install(TARGETS ph_static EXPORT ph_static-targets
#  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
