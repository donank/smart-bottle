cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_STANDARD 14)

#add_subdirectory("../../sensor" "${CMAKE_CURRENT_BINARY_DIR}/../../../build/sensor")
include_directories(../sensor)

project(turbidity VERSION 1.0.0 LANGUAGES CXX)
include(GNUInstallDirs)

add_compile_options(-Wall -Wconversion -Wextra -pedantic)

set(LIBSRC turbidity.cpp)
set(LIBINCLUDE turbidity.h)

add_library(turbidity
  SHARED
  ${LIBSRC}
  )

set_target_properties(turbidity PROPERTIES
  SOVERSION 1
  PUBLIC_HEADER "${LIBINCLUDE}")

target_link_libraries(turbidity sensor_static)

#install(TARGETS turbidity EXPORT turbidity-targets
#  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})



add_library(turbidity_static
  STATIC
  ${LIBSRC}
  )

set_target_properties(turbidity_static PROPERTIES
  PUBLIC_HEADER "${LIBINCLUDE}")

target_link_libraries(turbidity_static sensor_static)

#install(TARGETS turbidity_static EXPORT turbidity_static-targets
#  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
