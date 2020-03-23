cmake_minimum_required(VERSION 3.10)

add_subdirectory(lib)

add_executable(Engine src/main.cpp src/window.h src/window.cpp src/Scene.cpp src/Scene.h src/entities/Group.cpp src/entities/Model.cpp src/entities/Group.h src/entities/Model.h src/entities/Entity.cpp src/entities/Entity.h src/entities/Models.cpp src/entities/Models.h)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

if (NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif (NOT OPENGL_FOUND)

if (WIN32)
    set(GLUT_DIR "${CG_TP_SOURCE_DIR}/Engine/lib/glut")

    message(STATUS "GLUT_DIR set to: " ${GLUT_DIR})

    if (NOT EXISTS "${GLUT_DIR}/GL/glut.h" OR NOT EXISTS "${GLUT_DIR}/glut32.lib")
        message(ERROR ": GLUT not found: ${GLUT_DIR}/GL/glut.h")
    endif (NOT EXISTS "${GLUT_DIR}/GL/glut.h" OR NOT EXISTS "${GLUT_DIR}/glut32.lib")

    include_directories(${GLUT_DIR})
    link_directories(${GLUT_DIR})
    set(GLUT_LIBRARY ${GLUT_DIR}/glut32.lib)

    if (EXISTS "${GLUT_DIR}/glut32.dll")
        file(COPY ${GLUT_DIR}/glut32.dll DESTINATION ${CMAKE_BINARY_DIR}/Engine)
        file(COPY ${GLUT_DIR}/glut32.dll DESTINATION ${CG_TP_SOURCE_DIR}/Configurations)
    endif (EXISTS "${GLUT_DIR}/glut32.dll")

    set_property(DIRECTORY ${CG_TP_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Engine)
else (WIN32) # Include GLUT for Linux and Mac
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} Wno-deprecated")
    find_package(GLUT REQUIRED)

    include_directories(${GLUT_INCLUDE_DIR})
    link_directories(${GLUT_LIBRARY_DIRS})
    add_definitions(${GLUT_DEFINITIONS})

    if (NOT GLUT_FOUND)
        message(ERROR ": GLUT not found!")
    endif (NOT GLUT_FOUND)
endif (WIN32)

target_link_libraries(Engine ${OPENGL_LIBRARIES})
target_link_libraries(Engine ${GLUT_LIBRARY})
target_link_libraries(Engine Common)
target_link_libraries(Engine tinyxml2)
