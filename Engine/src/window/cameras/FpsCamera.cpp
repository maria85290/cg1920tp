#include "FpsCamera.h"

#include "../Window.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <glm/gtx/transform.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

using std::cout, std::endl;

namespace engine::window::cameras {
	void FpsCamera::InitCamera(Window* window, GLFWwindow* glfwWindow)
    {
        Camera::InitCamera(window, glfwWindow);
		
        SphericalToCartesian();

        lastMouseX = this->window->GetWidth() / 2.0;
        lastMouseY = this->window->GetHeight() / 2.0;

        glfwSetInputMode(this->glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
	
    FpsCamera::~FpsCamera() {
        glfwSetInputMode(this->glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }


    void FpsCamera::PrintInfo() {
        cout << "Use WASD or the arrow keys to move the camera, and the mouse to change the yaw/pitch." << endl;
        cout << "Press Q to speed up the camera movement, and E to slow it down." << endl;
        cout << "NOTE: To toggle the mouse movement, press ESCAPE!" << endl;
    }

    void FpsCamera::HandleKeyboardKeyPress(int key, int scanCode, int action, int mods) {
        if(action != GLFW_PRESS)
            return;

        glm::dvec3 forward = ComputeForward();
        glm::dvec3 right = ComputeRight(forward);

        forward = forward * speed;
        right = right * speed;

        switch(key) {
            case GLFW_KEY_W:
                cameraPos = glm::dvec3(cameraPos.x + forward.x, cameraPos.y + forward.y, cameraPos.z + forward.z);
                break;
            case GLFW_KEY_S:
                cameraPos = glm::dvec3(cameraPos.x - forward.x, cameraPos.y - forward.y, cameraPos.z - forward.z);
                break;
            case GLFW_KEY_A:
                cameraPos = glm::dvec3(cameraPos.x - right.x, cameraPos.y - right.y, cameraPos.z - right.z);
                break;
            case GLFW_KEY_D:
                cameraPos = glm::dvec3(cameraPos.x + right.x, cameraPos.y + right.y, cameraPos.z + right.z);
                break;
            case GLFW_KEY_Q:
                speed += 5;
                break;
            case GLFW_KEY_E:
                speed -= 5;

                if(speed < 0)
                    speed = 0;

                break;
            default:
                break;
        }

        SphericalToCartesian();
    }

    void FpsCamera::HandleMouseMovement(double mouseX, double mouseY) {
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

        SphericalToCartesian();
    }

    void FpsCamera::SphericalToCartesian() {
        // LookingAt = ... + cameraPos
        // Isto mantém o vetor forward com tamanho de 1 unidade

        lookingAt.x = glm::cos(pitch) * glm::sin(yaw) + cameraPos.x;
        lookingAt.y = glm::sin(pitch) + cameraPos.y;
        lookingAt.z = glm::cos(pitch) * glm::cos(yaw) + cameraPos.z;

        this->viewMatrix = glm::lookAt(
            cameraPos,
            lookingAt,
            glm::dvec3(0, 1, 0) // Up vector
        );
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
}
