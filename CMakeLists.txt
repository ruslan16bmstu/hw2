cmake_minimum_required(VERSION 3.9)
project(Parallel)

SET(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage -pthread")
SET(CMAKE_C_FLAGS "-g -O0 -Wall -W -D_DEBUG -fprofile-arcs -ftest-coverage --coverage -Wpedantic")
SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

include_directories(${PROJECT_SOURCE_DIR}/src/standard ${PROJECT_SOURCE_DIR}/src/parallel ${PROJECT_SOURCE_DIR}/src/main)

add_library(standard STATIC ${PROJECT_SOURCE_DIR}/src/main/mylib.c ${PROJECT_SOURCE_DIR}/src/standard/standard.c)

add_library(parallel SHARED ${PROJECT_SOURCE_DIR}/src/main/mylib.c ${PROJECT_SOURCE_DIR}/src/parallel/parallel.c)

enable_testing()

add_executable(Parallel ${PROJECT_SOURCE_DIR}/src/main/main_parallel.c)
target_link_libraries(Parallel parallel)

add_executable(Standard ${PROJECT_SOURCE_DIR}/src/main/main_standard.c)
target_link_libraries(Standard standard)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(mytests src/test/mytests.cpp)
target_link_libraries(mytests ${GTEST_LIBRARIES})
target_link_libraries(mytests parallel standard)

add_executable(stress src/test/stress_test.cpp)
target_link_libraries(stress ${GTEST_LIBRARIES})
target_link_libraries(stress parallel standard)
