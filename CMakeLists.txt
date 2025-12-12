cmake_minimum_required(VERSION 3.30)

project(MyCProgram C)

set(CMAKE_DISABLE_IN_SOURCE_BUILD TRUE)
enable_testing()

add_library(matrix_mul STATIC)
target_include_directories(matrix_mul PUBLIC include)
target_sources(matrix_mul PRIVATE lib/matrix_mul.c)

add_executable(driver src/main.c)
target_link_libraries(driver PRIVATE matrix_mul)
#target_include_directories(driver PRIVATE include)

#foreach(size RANGE 2 3)
#  add_test(NAME ${size}x${size} COMMAND matrix_mul ${size} ${size})
#endforeach()
