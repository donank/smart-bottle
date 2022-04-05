cmake_minimum_required(VERSION 3.10)

add_subdirectory(rpi_ads1115)
add_subdirectory(circularbuffer)

project(main VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(main main.cpp)


target_link_libraries(main ads1115rpi_static circularbuffer_static)
target_include_directories(main PRIVATE rpi_ads1115 circularbuffer)



