cmake_minimum_required(VERSION 3.10)

add_executable(Engine
        src/main.cpp
        src/scene/Scene.cpp src/scene/Scene.h
        src/scene/entities/Group.cpp src/scene/entities/Group.h
        src/scene/entities/Model.cpp src/scene/entities/Model.h
        src/scene/entities/Entity.cpp src/scene/entities/Entity.h
        src/scene/entities/Models.cpp src/scene/entities/Models.h
        src/scene/entities/StaticTranslate.cpp src/scene/entities/StaticTranslate.h
        src/scene/entities/StaticRotate.cpp src/scene/entities/StaticRotate.h
        src/scene/entities/Scale.cpp src/scene/entities/Scale.h
        src/scene/entities/TimedRotate.cpp src/scene/entities/TimedRotate.h
        src/scene/entities/CatmullRomAnimation.cpp src/scene/entities/CatmullRomAnimation.h
        src/objects/ObjectCache.h
        src/objects/ModelMesh.cpp src/objects/ModelMesh.h
        src/objects/Texture.cpp src/objects/Texture.h
        src/window/Window.cpp src/window/Window.h
        src/window/cameras/Camera.h
        src/window/cameras/FpsCamera.cpp src/window/cameras/FpsCamera.h
        src/window/cameras/StaticCamera.cpp src/window/cameras/StaticCamera.h
        src/window/cameras/ExplorerCamera.cpp src/window/cameras/ExplorerCamera.h
        src/window/input/Keyboard.cpp src/window/input/Keyboard.h
        src/util/Settings.cpp src/util/Settings.h
        src/scene/lighting/Lights.cpp src/scene/lighting/Lights.h
        src/scene/lighting/Light.h src/scene/lighting/Light.cpp
        src/scene/lighting/PointLight.cpp src/scene/lighting/PointLight.h
        src/scene/lighting/DirectionalLight.h src/scene/lighting/DirectionalLight.cpp)

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
        set(DEVIL_DIR "${TOOLKITS_DIR}/devil/x32")
	else ()
		set(GLFW_DIR "${TOOLKITS_DIR}/glfw/x64")
        set(DEVIL_DIR "${TOOLKITS_DIR}/devil/x64")
	endif ()

    if (NOT EXISTS "${GLFW_DIR}/include/GLFW/glfw3.h" OR NOT EXISTS "${GLFW_DIR}/lib/glfw3.lib")
        message(ERROR ": GLFW not found: ${GLFW_DIR}/include/GLFW/glfw3.h")
    endif ()

    if (NOT EXISTS "${DEVIL_DIR}/include/IL/il.h" OR NOT EXISTS "${DEVIL_DIR}/DevIL.lib")
        message(ERROR ": DevIL not found: ${DEVIL_DIR}/include/IL/il.h")
    endif ()

    target_include_directories(Engine PUBLIC ${GLFW_DIR}/include)
    target_include_directories(Engine PUBLIC ${DEVIL_DIR}/include)

    if (EXISTS "${GLFW_DIR}/bin/glfw3.dll" AND EXISTS "${DEVIL_DIR}/DevIL.dll")
        file(COPY ${GLFW_DIR}/bin/glfw3.dll DESTINATION ${CMAKE_BINARY_DIR}/Engine)
        file(COPY ${GLFW_DIR}/bin/glfw3.dll DESTINATION ${CG_TP_SOURCE_DIR}/Configurations)
        file(COPY ${DEVIL_DIR}/DevIL.dll DESTINATION ${CMAKE_BINARY_DIR}/Engine)
        file(COPY ${DEVIL_DIR}/DevIL.dll DESTINATION ${CG_TP_SOURCE_DIR}/Configurations)
    endif ()

    target_link_libraries(Engine PUBLIC ${GLFW_DIR}/lib/glfw3.lib ${GLFW_DIR}/lib/glfw3dll.lib)
    target_link_libraries(Engine PUBLIC ${DEVIL_DIR}/DevIL.lib)

    set_property(DIRECTORY ${CG_TP_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Engine)
elseif(UNIX AND NOT APPLE) # Include GLUT and GLEW for Linux
    set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl -lglfw") # Add -ldl to the command line for cc

    find_package(glfw3 REQUIRED)
    find_package(DevIL REQUIRED)

    if(NOT glfw3_FOUND)
        message(ERROR ": GLFW not found!")
        message(ERROR ": To install on Linux, use your distribution's package manager.")
        message(ERROR ": On Debian-based systems, install package libglfw3-dev")
    endif()

    if(NOT DevIL_FOUND)
        message(ERROR ": DevIL not found!")
        message(ERROR ": Please install it from your distribution's package manager.")
    endif()

    target_include_directories(Engine PUBLIC ${GLFW_INCLUDE_DIR} ${IL_INCLUDE_DIR})
    target_link_libraries(Engine PUBLIC glfw DevIL ${CMAKE_DL_LIBS})
elseif(APPLE)
    set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl") # Add -ldl to the command line for cc

    find_package(GLFW3 REQUIRED)
    find_package(DevIL REQUIRED)

    if(NOT glfw3_FOUND)
        message(ERROR ": GLFW not found!")
        message(ERROR ": Use homebrew to install: brew install glfw3")
    endif()

    if(NOT DevIL_FOUND)
        message(ERROR ": DevIL not found!")
        message(ERROR ": Please install it from homebrew.")
    endif()

    target_include_directories(Engine PUBLIC ${GLFW_INCLUDE_DIR} ${IL_INCLUDE_DIR})
    target_link_libraries(Engine PUBLIC glfw DevIL ${CMAKE_DL_LIBS})
endif()

target_link_libraries(Engine PUBLIC glad)
target_link_libraries(Engine PUBLIC glm)
target_link_libraries(Engine PUBLIC tinyxml2)
