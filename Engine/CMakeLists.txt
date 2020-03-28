cmake_minimum_required(VERSION 3.10)

add_subdirectory(lib)

add_executable(Engine
        src/main.cpp
        src/Scene.cpp src/Scene.h
        src/entities/Group.cpp src/entities/Group.h
        src/entities/Model.cpp src/entities/Model.h
        src/entities/Entity.cpp src/entities/Entity.h
        src/entities/Models.cpp src/entities/Models.h
        src/entities/Translate.cpp src/entities/Translate.h
        src/entities/Rotate.cpp src/entities/Rotate.h
        src/entities/Scale.cpp src/entities/Scale.h
        src/window/Window.cpp src/window/Window.h
        src/window/cameras/Camera.h
        src/window/cameras/FpsCamera.cpp src/window/cameras/FpsCamera.h
        src/window/cameras/ExplorerCamera.cpp src/window/cameras/ExplorerCamera.h)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

if (NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif (NOT OPENGL_FOUND)

if (WIN32)
    set(TOOLKITS_DIR "${CG_TP_SOURCE_DIR}/Engine/lib")

    message(STATUS "TOOLKITS_DIR set to: " ${TOOLKITS_DIR})

    if (NOT EXISTS "${TOOLKITS_DIR}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_DIR}/glut/glut32.lib")
        message(ERROR ": GLUT not found: ${TOOLKITS_DIR}/glut/GL/glut.h")
    endif (NOT EXISTS "${TOOLKITS_DIR}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_DIR}/glut/glut32.lib")

    if (NOT EXISTS "${TOOLKITS_DIR}/glew/GL/glew.h" OR NOT EXISTS "${TOOLKITS_DIR}/glew/glew32.lib")
        message(ERROR ": GLEW not found")
    endif (NOT EXISTS "${TOOLKITS_DIR}/glew/GL/glew.h" OR NOT EXISTS "${TOOLKITS_DIR}/glew/glew32.lib")

    include_directories(${TOOLKITS_DIR}/glut ${TOOLKITS_DIR}/glew)
    link_directories(${TOOLKITS_DIR}/glut ${TOOLKITS_DIR}/glew)
    set(GLUT_LIBRARY ${TOOLKITS_DIR}/glut/glut32.lib)
    set(GLEW_LIBRARY ${TOOLKITS_DIR}/glew/glew32.lib)

    if (EXISTS "${TOOLKITS_DIR}/glut/glut32.dll")
        file(COPY ${TOOLKITS_DIR}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR}/Engine)
        file(COPY ${TOOLKITS_DIR}/glut/glut32.dll DESTINATION ${CG_TP_SOURCE_DIR}/Configurations)
    endif (EXISTS "${TOOLKITS_DIR}/glut/glut32.dll")

    if (EXISTS "${TOOLKITS_DIR}/glew/glew32.dll")
        file(COPY ${TOOLKITS_DIR}/glew/glew32.dll DESTINATION ${CMAKE_BINARY_DIR}/Engine)
        file(COPY ${TOOLKITS_DIR}/glew/glew32.dll DESTINATION ${CG_TP_SOURCE_DIR}/Configurations)
    endif (EXISTS "${TOOLKITS_DIR}/glew/glew32.dll")

    set_property(DIRECTORY ${CG_TP_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Engine)
else (WIN32) # Include GLUT and GLEW for Linux and Mac
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} Wno-deprecated")

    find_package(GLUT REQUIRED)

    if (NOT GLUT_FOUND)
        message(ERROR ": GLUT not found!")
    endif (NOT GLUT_FOUND)

    include_directories(${GLUT_INCLUDE_DIR})
    link_directories(${GLUT_LIBRARY_DIRS})
    add_definitions(${GLUT_DEFINITIONS})

    if(NOT APPLE)
        find_package(GLEW REQUIRED)
        if (NOT GLEW_FOUND)
            message(ERROR ": GLEW not found!")
        endif(NOT GLEW_FOUND)

        include_directories(${GLEW_INCLUDE_DIRS})
        link_directories(${GLEW_LIBRARIES})
    endif(NOT APPLE)
endif (WIN32)

target_link_libraries(Engine ${OPENGL_LIBRARIES})
target_link_libraries(Engine ${GLUT_LIBRARY})
if(NOT APPLE)
    target_link_libraries(Engine ${GLEW_LIBRARY})
endif(NOT APPLE)
target_link_libraries(Engine Common)
target_link_libraries(Engine tinyxml2)
