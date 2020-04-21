cmake_minimum_required(VERSION 3.10)

add_executable(Generator src/AbstractGenerator.h src/PlaneGenerator.cpp src/PlaneGenerator.h src/main.cpp src/BoxGenerator.cpp src/BoxGenerator.h src/SphereGenerator.cpp src/SphereGenerator.h src/ConeGenerator.cpp src/ConeGenerator.h)

target_link_libraries(Generator glm)
