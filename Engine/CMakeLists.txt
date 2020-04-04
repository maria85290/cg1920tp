cmake_minimum_required(VERSION 3.10)

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
        src/window/cameras/StaticCamera.cpp src/window/cameras/StaticCamera.h)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

if (NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif ()

if (WIN32)
    set(TOOLKITS_DIR "${CG_TP_SOURCE_DIR}/lib")

    message(STATUS "TOOLKITS_DIR set to: " ${TOOLKITS_DIR})

    if (NOT EXISTS "${TOOLKITS_DIR}/glfw/include/GLFW/glfw3.h" OR NOT EXISTS "${TOOLKITS_DIR}/glfw/lib/glfw3.lib")
        message(ERROR ": GLFW not found: ${TOOLKITS_DIR}/glfw/include/GLFW/glfw3.h")
    endif ()

    if (NOT EXISTS "${TOOLKITS_DIR}/glbindingwin/include/glbinding/glbinding.h" OR NOT EXISTS "${TOOLKITS_DIR}/glbindingwin/lib/glbinding.lib")
        message(ERROR ": glbinding not found")
    endif ()

    target_include_directories(Engine
            PUBLIC ${TOOLKITS_DIR}/glfw/include
            PUBLIC ${TOOLKITS_DIR}/glbindingwin/include)

    if (EXISTS "${TOOLKITS_DIR}/glfw/bin/glfw3.dll")
        file(COPY ${TOOLKITS_DIR}/glfw/bin/glfw3.dll DESTINATION ${CMAKE_BINARY_DIR}/Engine)
        file(COPY ${TOOLKITS_DIR}/glfw/bin/glfw3.dll DESTINATION ${CG_TP_SOURCE_DIR}/Configurations)
    endif ()

    if (EXISTS "${TOOLKITS_DIR}/glbindingwin/bin/glbinding.dll")
        file(COPY ${TOOLKITS_DIR}/glbindingwin/bin/glbinding.dll DESTINATION ${CMAKE_BINARY_DIR}/Engine)
        file(COPY ${TOOLKITS_DIR}/glbindingwin/bin/glbinding.dll DESTINATION ${CG_TP_SOURCE_DIR}/Configurations)
    endif ()

    target_link_libraries(Engine ${TOOLKITS_DIR}/glfw/lib/glfw3.lib ${TOOLKITS_DIR}/glbindingwin/lib/glbinding.lib)

    set_property(DIRECTORY ${CG_TP_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Engine)
elseif(UNIX AND NOT APPLE) # Include GLUT and GLEW for Linux
    find_package(glfw3 REQUIRED)
    find_package(glbinding REQUIRED)

    if(NOT glfw3_FOUND)
        message(ERROR ": GLFW not found!")
        message(ERROR ": To install on Linux, use your distribution's package manager.")
        message(ERROR ": On Debian-based systems, install package libglfw3-dev")
    endif()

    if(NOT glbinding_FOUND)
        message(ERROR ": glbinding not found!")
        message(ERROR ": To install on Linux, use your distribution's package manager.")
        message(ERROR ": On Ubuntu-based systems, install package libglbinding-dev.")
    endif()

    target_link_libraries(Engine glfw)
    target_link_libraries(Engine glbinding::glbinding glbinding::glbinding-aux)
elseif(APPLE)
    find_package(glfw3 REQUIRED)
    find_package(glbinding 3.0 REQUIRED)

    if(NOT glfw3_FOUND)
        message(ERROR ": GLFW not found!")
        message(ERROR ": Use homebrew to install: brew install glfw3")
    endif()

    if(NOT glbinding_FOUND)
        message(ERROR ": glbinding not found!")
        message(ERROR ": Use homebrew to install: brew install glbinding")
    endif()

    target_link_libraries(Engine glfw)
    target_link_libraries(Engine glbinding::glbinding)
endif()

target_link_libraries(Engine OpenGL::GL)
target_link_libraries(Engine tinyxml2)
target_link_libraries(Engine glm)
