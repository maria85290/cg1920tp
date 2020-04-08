cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE HEADERS include/*.h*)

add_library(glad STATIC ${HEADERS} src/glad.c)

target_include_directories(glad PUBLIC include)
