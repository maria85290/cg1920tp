cmake_minimum_required(VERSION 3.10)

add_executable(Generator src/PlaneGenerator.cpp src/PlaneGenerator.h src/AbstractGenerator.h src/main.cpp)

target_link_libraries(Generator Common)
