file(GLOB_RECURSE HEADERS include/*.h*)

add_library(Common STATIC ${HEADERS} src/test.cpp)

target_include_directories(Common PUBLIC include)
