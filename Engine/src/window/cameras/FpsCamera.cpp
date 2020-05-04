#include "FpsCamera.h"

#include "../Window.h"

#include <glm/gtx/transform.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

using std::cout, std::endl;
using std::fmod, glm::pi;
using engine::window::input::Keyboard;

namespace engine::window::cameras {
    void FpsCamera::InitCamera(Window* window, GLFWwindow* glfwWindow) {
        Camera::InitCamera(window, glfwWindow);
        SphericalToCartesian();

        glfwSetInputMode(this->glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwGetCursorPos(this->glfwWindow, &lastMouseX, &lastMouseY);
    }

    FpsCamera::~FpsCamera() {
        glfwSetInputMode(this->glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    void FpsCamera::PrintInfo() const {
        cout << "Use WASD or the arrow keys to move the camera, and the mouse to change the yaw/pitch." << endl;
        cout << "Press Q to speed up the camera movement, and E to slow it down." << endl;
        cout << "Press F3 to show debugging elements, such as Catmull-Rom Curves, or the axis at the origin of the world." << endl;
    }

    void FpsCamera::UpdatePosition() {
        glm::dvec3 deltaPos = glm::dvec3(0.0, 0.0, 0.0);

        glm::dvec3 forward = ComputeForward();
        glm::dvec3 right = ComputeRight(forward);

        if(Keyboard::isKeyDown(GLFW_KEY_W)) {
            deltaPos += forward;
        }

        if(Keyboard::isKeyDown(GLFW_KEY_S)) {
            deltaPos -= forward;
        }

        if(Keyboard::isKeyDown(GLFW_KEY_A)) {
            deltaPos -= right;
        }

        if(Keyboard::isKeyDown(GLFW_KEY_D)) {
            deltaPos += right;
        }

        cameraPos += (deltaPos * speed * this->window->GetDeltaTime());

        SphericalToCartesian();

        this->viewMatrix = glm::lookAt(
            cameraPos,
            lookingAt,
            glm::dvec3(0, 1, 0) // Up vector
        );
    }

    void FpsCamera::HandleKeyboardKeyPress(int key, int scanCode, int action, int mods) {
        if(key == GLFW_KEY_F2 && action == GLFW_PRESS) {
            cout << "[Debug] Coordenadas da camara: ("
                << this->cameraPos.x << ", " << this->cameraPos.y << ", " << this->cameraPos.z << ")" << endl;
            cout << "[Debug] Camara a olhar para: ("
                << this->lookingAt.x << ", " << this->lookingAt.y << ", " << this->lookingAt.z << ")" << endl;
        }
    }

    void FpsCamera::HandleMouseMovement(double mouseX, double mouseY) {
        if(!window->IsFocused())
            return; // Do not update the camera view unless the user has the window in focus

        double deltaX = lastMouseX - mouseX;
        double deltaY = lastMouseY - mouseY;

        yaw += 0.001f * deltaX;
        yaw = fmod(yaw, 2.0 * M_PI); // camAlpha %= 360

        pitch += 0.001f * deltaY;

        if(pitch < -M_PI_2) {
            pitch = -M_PI_2 + 0.0001f;
        } else if(pitch > M_PI_2) {
            pitch = M_PI_2 - 0.0001f;
        }

        lastMouseX = mouseX;
        lastMouseY = mouseY;
    }

    void FpsCamera::HandleScrollMovement(double xOffset, double yOffset) {
        speed += yOffset * 3;

        if(speed < 0.0)
            speed = 2.0;
    }

    glm::dvec3 FpsCamera::ComputeForward() {
        return glm::normalize(glm::dvec3(
            lookingAt.x - cameraPos.x,
            lookingAt.y - cameraPos.y,
            lookingAt.z - cameraPos.z
        ));
    }

    glm::dvec3 FpsCamera::ComputeRight(glm::dvec3 forward) {
        const glm::dvec3 up(0, 1, 0);

        return glm::normalize(glm::cross(forward, up));
    }

    glm::dvec3 FpsCamera::ComputeRight() {
        return this->ComputeRight(this->ComputeForward());
    }

    void FpsCamera::SphericalToCartesian() {
        lookingAt = cameraPos + glm::dvec3(
            glm::cos(pitch) * glm::sin(yaw),
            glm::sin(pitch),
            glm::cos(pitch) * glm::cos(yaw)
        );
    }
}
