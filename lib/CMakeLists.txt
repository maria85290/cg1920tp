cmake_minimum_required(VERSION 3.10)

# Includes all library projects necessary

add_subdirectory(tinyxml2)
add_subdirectory(glm)
add_subdirectory(glad)
if(UNIX AND NOT APPLE)
# add_subdirectory(glbindinglinux)
endif()
