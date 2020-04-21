#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

#include "StaticCamera.h"

using namespace std;

namespace engine::window::cameras {
    StaticCamera::StaticCamera(glm::dvec3 position, glm::dvec3 lookingAt):
    position(position), lookingAt(lookingAt)
    {
        this->viewMatrix = glm::lookAt(
            position,
            lookingAt,
            glm::dvec3(0, 1, 0) // Up vector
        );
    }
}
