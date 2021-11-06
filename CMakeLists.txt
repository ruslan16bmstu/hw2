cmake_minimum_required(VERSION 3.9)
project(Parallel)

SET(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage -pthread")
SET(CMAKE_C_FLAGS "-g -O0 -Wall -W -D_DEBUG -fprofile-arcs -ftest-coverage")
SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

add_library(standard STATIC ${PROJECT_SOURCE_DIR}/src/mylib.c ${PROJECT_SOURCE_DIR}/src/standard.c)

add_library(parallel SHARED ${PROJECT_SOURCE_DIR}/src/mylib.c ${PROJECT_SOURCE_DIR}/src/parallel.c)

include_directories(src/standard src/parallel src/main)

add_library(mylib STATIC mylib.c mylib.h)

add_executable(main main.c)
target_link_libraries(main mylib)

include_directories(${GTEST_INCLUDE_DIRS})