cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE HEADERS include/*.h*)

add_library(tinyxml2 STATIC ${HEADERS} src/tinyxml2.cpp)

target_include_directories(tinyxml2 PUBLIC include)
