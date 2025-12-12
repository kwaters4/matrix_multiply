cmake_minimum_required(VERSION 3.30)

project(MyCProgram C)

set(CMAKE_DISABLE_IN_SOURCE_BUILD TRUE)
enable_testing()

add_library(matrix_mul lib/matrix_mul.c)
target_include_directories(matrix_mul PUBLIC include/matrix_mul.h)

add_executable(driver src/main.c)
target_link_libraries(driver PRIVATE matrix_mul)
#target_include_directories(driver include/matrix_mul.h)

#foreach(size RANGE 2 3)
#  add_test(NAME ${size}x${size} COMMAND matrix_mul ${size} ${size})
#endforeach()
