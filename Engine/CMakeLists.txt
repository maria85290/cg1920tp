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
        src/window/cameras/StaticCamera.cpp src/window/cameras/StaticCamera.h
        src/window/cameras/ExplorerCamera.cpp src/window/cameras/ExplorerCamera.h
        src/window/input/Keyboard.cpp src/window/input/Keyboard.h)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED COMPONENTS OpenGL)

if (NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif ()

target_link_libraries(Engine PUBLIC OpenGL::GL)

if (WIN32)
    set(TOOLKITS_DIR "${CG_TP_SOURCE_DIR}/lib")
    message(STATUS "TOOLKITS_DIR set to: " ${TOOLKITS_DIR})
	
	if (NOT CMAKE_CL_64)
		set(GLFW_DIR "${TOOLKITS_DIR}/glfw/x32")
	else ()
		set(GLFW_DIR "${TOOLKITS_DIR}/glfw/x64")
	endif ()

    if (NOT EXISTS "${GLFW_DIR}/include/GLFW/glfw3.h" OR NOT EXISTS "${GLFW_DIR}/lib/glfw3.lib")
        message(ERROR ": GLFW not found: ${GLFW_DIR}/include/GLFW/glfw3.h")
    endif ()

    target_include_directories(Engine PUBLIC ${GLFW_DIR}/include)

    if (EXISTS "${GLFW_DIR}/bin/glfw3.dll")
        file(COPY ${GLFW_DIR}/bin/glfw3.dll DESTINATION ${CMAKE_BINARY_DIR}/Engine)
        file(COPY ${GLFW_DIR}/bin/glfw3.dll DESTINATION ${CG_TP_SOURCE_DIR}/Configurations)
    endif ()

    target_link_libraries(Engine PUBLIC ${GLFW_DIR}/lib/glfw3.lib ${GLFW_DIR}/lib/glfw3dll.lib)

    set_property(DIRECTORY ${CG_TP_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Engine)
elseif(UNIX AND NOT APPLE) # Include GLUT and GLEW for Linux
    set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl -lglfw") # Add -ldl to the command line for cc

    find_package(glfw3 REQUIRED)

    if(NOT glfw3_FOUND)
        message(ERROR ": GLFW not found!")
        message(ERROR ": To install on Linux, use your distribution's package manager.")
        message(ERROR ": On Debian-based systems, install package libglfw3-dev")
    endif()

    target_link_libraries(Engine PUBLIC glfw ${CMAKE_DL_LIBS})
elseif(APPLE)
    set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl") # Add -ldl to the command line for cc

    find_package(GLFW3 REQUIRED)

    if(NOT glfw3_FOUND)
        message(ERROR ": GLFW not found!")
        message(ERROR ": Use homebrew to install: brew install glfw3")
    endif()

    target_include_directories(Engine PUBLIC ${GLFW_INCLUDE_DIR})
    target_link_libraries(Engine PUBLIC glfw ${CMAKE_DL_LIBS})
endif()

target_link_libraries(Engine PUBLIC glad)
target_link_libraries(Engine PUBLIC glm)
target_link_libraries(Engine PUBLIC tinyxml2)
