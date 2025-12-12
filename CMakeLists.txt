cmake_minimum_required(VERSION 3.30)

project(MatrixMultiplication VERSION 0.1 LANGUAGES C)

add_library(matrix_mul STATIC)
target_include_directories(matrix_mul PUBLIC include)
target_sources(matrix_mul PRIVATE lib/matrix_mul.c)

add_executable(driver src/main.c)
target_link_libraries(driver PRIVATE matrix_mul)


if(ENABLE_TESTING)
  enable_testing()
  add_executable(matrix_gen test/matrix_gen.c)
  target_link_libraries(matrix_gen PRIVATE matrix_mul)
  add_test(NAME matrix_gen COMMAND matrix_gen 2 5)
endif()
