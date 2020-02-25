cmake_minimum_required(VERSION 3.10)

add_subdirectory(lib)

add_executable(Engine src/main.cpp src/Scene.cpp src/Model.cpp)

target_link_libraries(Engine ${OPENGL_LIBRARIES})
target_link_libraries(Engine ${GLUT_LIBRARY})
target_link_libraries(Engine Common)
target_link_libraries(Engine tinyxml2)
