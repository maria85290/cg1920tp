cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE HEADERS include/*.h*)

add_library(Common STATIC ${HEADERS} src/vectors.cpp)

target_include_directories(Common PUBLIC include)
