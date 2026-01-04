cmake_minimum_required(VERSION 3.30)

project(MatrixMultiplication VERSION 0.1 LANGUAGES C)

# Set BLOCK_SIZE for tiled atrix multiply

set(BLOCK_SIZE "32" CACHE STRING "BLOCK_SIZE for matrix multiply")
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/include/matrix_mul.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/matrix_mul.h"
    @ONLY
)

add_library(matrix_mul STATIC)
target_include_directories(matrix_mul PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_sources(matrix_mul PRIVATE lib/matrix_mul.c)

add_library(timer STATIC)
target_include_directories(timer PUBLIC include)
target_sources(timer PRIVATE lib/timer.c)

add_library(test_library STATIC)
target_include_directories(test_library PUBLIC include)
target_include_directories(test_library PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_sources(test_library PRIVATE lib/test_library.c)

add_executable(driver src/main.c)
target_link_libraries(driver PRIVATE matrix_mul timer)

set(CMAKE_C_FLAGS "-Wall -O3 -march=native -funroll-loops")

if(ENABLE_TESTING)
  enable_testing()
  # Find and Loop through each file in the './test directory'
  set(TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test")
  file(GLOB test_files RELATIVE "${TEST_DIR}" "${TEST_DIR}/*.c")
  foreach(file ${test_files})
      string(REPLACE ".c" "" target_name ${file})
      add_executable(${target_name} "${TEST_DIR}/${file}")
      target_link_libraries(${target_name} PRIVATE matrix_mul test_library timer)
      add_test(NAME ${target_name} COMMAND ${target_name})
  endforeach()
endif()

# Install the built library target
install(TARGETS timer DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(TARGETS test_library DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(TARGETS matrix_mul DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

install(TARGETS driver DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/matrix_mul.h"
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
)

install(DIRECTORY include/
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include
        FILES_MATCHING
        PATTERN "*.h"
)

