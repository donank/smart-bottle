cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif()

project(circularbuffer VERSION 1.0.0 LANGUAGES CXX)

set(LIBSRC circularbufferinstantiated.cpp)
set(LIBINCLUDE circularbuffer.h)

add_library(circularbuffer
  SHARED
  ${LIBSRC}
  )

set_target_properties(circularbuffer PROPERTIES
  SOVERSION 1
  PUBLIC_HEADER "${LIBINCLUDE}")

target_link_libraries(circularbuffer PUBLIC)

install(TARGETS circularbuffer EXPORT circularbuffer-targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

add_library(circularbuffer_static
  STATIC
  ${LIBSRC}
  )

set_target_properties(circularbuffer_static PROPERTIES
  PUBLIC_HEADER "${LIBINCLUDE}")

target_link_libraries(circularbuffer_static PUBLIC)


install(TARGETS circularbuffer_static EXPORT circularbuffer_static-targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

  target_include_directories(circularbuffer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
  set(A "Circ Buffer")



