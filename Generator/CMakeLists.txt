cmake_minimum_required(VERSION 3.10)

add_executable(Generator
        src/main.cpp
        src/AbstractGenerator.h src/AbstractGenerator.cpp
        src/PlaneGenerator.cpp src/PlaneGenerator.h
        src/BoxGenerator.cpp src/BoxGenerator.h
        src/SphereGenerator.cpp src/SphereGenerator.h
	src/BezierGenerator.cpp src/BezierGenerator.h
        src/ConeGenerator.cpp src/ConeGenerator.h)

target_link_libraries(Generator glm)
