cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_STANDARD 11)

project(circularbuffer VERSION 1.0.0 LANGUAGES CXX)

set(LIBSRC circularbuffer.cpp)
set(LIBINCLUDE circularbuffer.h)

add_library(circularbuffer
  SHARED
  ${LIBSRC}
  )

target_link_libraries(circularbuffer PUBLIC)

add_library(circularbuffer_static
  STATIC
  ${LIBSRC}
  )

target_link_libraries(circularbuffer_static)



