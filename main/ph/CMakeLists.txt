cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_STANDARD 14)

#add_subdirectory("../sensor" "../../build/sensor")
include_directories(../sensor)

project(ph VERSION 1.0.0 LANGUAGES CXX)
include(GNUInstallDirs)

add_compile_options(-Wall -Wconversion -Wextra -pedantic)

set(LIBSRC ph.cpp)
set(LIBINCLUDE ph.h)

add_library(ph
  SHARED
  ${LIBSRC}
  )

set_target_properties(ph PROPERTIES
  SOVERSION 1
  PUBLIC_HEADER "${LIBINCLUDE}")

target_link_libraries(ph sensor_static)

#install(TARGETS ph EXPORT ph-targets
#  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})



add_library(ph_static
  STATIC
  ${LIBSRC}
  )

set_target_properties(ph_static PROPERTIES
  PUBLIC_HEADER "${LIBINCLUDE}")

target_link_libraries(ph_static sensor_static)

#install(TARGETS ph_static EXPORT ph_static-targets
#  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
