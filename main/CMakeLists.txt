cmake_minimum_required(VERSION 3.10)

project(main VERSION 1.0)

message("top: CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
message("top: CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")
message("top: CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
message("top: CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}")

add_subdirectory(rpi_ads1115)
add_subdirectory(circularbuffer)
message("rpi included")
add_subdirectory(sensor)
add_subdirectory(ph)
message("ph included")
add_subdirectory(turbidity)
message("turbidity inluded")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(main main.cpp)

target_link_libraries(main ads1115rpi_static ph_static turbidity_static)
target_include_directories(main PRIVATE rpi_ads1115 ph turbidity)



