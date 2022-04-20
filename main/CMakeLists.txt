cmake_minimum_required(VERSION 3.10)

#project(main VERSION 1.0)

add_subdirectory(ads1115rpi)
add_subdirectory(sensor)
add_subdirectory(ph)
add_subdirectory(turbidity)
add_subdirectory(temperature)
add_subdirectory(volume)
find_package (Threads)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(main main.cpp)

target_link_libraries(main fcgi curl rt ${CMAKE_THREAD_LIBS_INIT} ads1115rpi_static ph_static turbidity_static temperature_static volume_static)
target_include_directories(main PRIVATE rpi_ads1115 ph turbidity temperature volume)



