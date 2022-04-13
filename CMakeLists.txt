cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_STANDARD 14)

project(json_fastcgi_web_api)

add_subdirectory(fake_sensor_demo)

find_package( CURL )

add_library(json-fastcgi INTERFACE)

target_include_directories(json-fastcgi INTERFACE .)

TARGET_LINK_LIBRARIES(json-fastcgi INTERFACE fcgi curl)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif()

set_property(TARGET json-fastcgi PROPERTY PUBLIC_HEADER json_fastcgi_web_api.h)

install(TARGETS json-fastcgi PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
