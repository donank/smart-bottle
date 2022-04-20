cmake_minimum_required (VERSION 3.1.0)
project (Oshun)
add_subdirectory(main)
add_subdirectory(tests)


enable_testing()
add_test (NAME Test COMMAND Test)