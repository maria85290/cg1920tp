cmake_minimum_required(VERSION 3.9)

project(CG_TP)

set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(Common)
add_subdirectory(Generator)
add_subdirectory(Engine)
