#include <iostream>

#include <glad/glad.h>

#include <glm/vec3.hpp>

#define _USE_MATH_DEFINES
#include <math.h>
#include <glm/ext/matrix_transform.hpp>

#include "ExplorerCamera.h"

using std::cout, std::endl;

namespace engine::window::cameras {
    ExplorerCamera::ExplorerCamera(glm::dvec3 center): center(center) {}

    void ExplorerCamera::InitCamera(Window *window, GLFWwindow *glfwWindow) {
        Camera::InitCamera(window, glfwWindow);

        SphericalToCartesian();

        glfwGetCursorPos(this->glfwWindow, &lastMouseX, &lastMouseY);
    }

    void ExplorerCamera::PrintInfo() const {
        cout << "Use left click and move mouse to adjust camera position," << endl;
        cout << "and use right click to zoom in and out." << endl;
    }

    void ExplorerCamera::UpdatePosition() {
        this->viewMatrix = glm::lookAt(cameraPos, center, glm::dvec3(0, 1, 0));
    }

    /**
     * Callback do Glut para quando o utilizador clica (ou larga) uma tecla do rato.
     *
     * @param button
     * @param action
     * @param mods
     */
    void ExplorerCamera::HandleMouseKeyPress(int button, int action, int mods) {
        switch(button) {
            case GLFW_MOUSE_BUTTON_LEFT:
                leftMousePressed = action == GLFW_PRESS;
                break;
            case GLFW_MOUSE_BUTTON_RIGHT:
                rightMousePressed = action == GLFW_PRESS;
                break;
            default:
                break;
        }

        glfwGetCursorPos(this->glfwWindow, &lastMouseX, &lastMouseY);
    }

    /**
     * Callback do Glut para quando um utilizador movimenta o rato, e uma das teclas está pressionada.
     *
     * @param mouseX
     * @param mouseY
     */
    void ExplorerCamera::HandleMouseMovement(double mouseX, double mouseY) {
        double deltaX = lastMouseX - mouseX;
        double deltaY = mouseY - lastMouseY;

        if(leftMousePressed) {
            camAlpha += 0.001 * deltaX;
            camAlpha = fmod(camAlpha, 2 * M_PI); // camAlpha %= 360

            camBeta += 0.001 * deltaY;

            if(camBeta < -M_PI_2) {
                camBeta = -M_PI_2;
            } else if(camBeta > M_PI_2) {
                camBeta = M_PI_2;
            }
        } else if(rightMousePressed) {
            camRadius -= 0.05 * deltaY;

            if(camRadius < 5.0) {
                camRadius = 5.0;
            }
        }

        lastMouseX = mouseX;
        lastMouseY = mouseY;

        SphericalToCartesian();
    }

    /**
     * Converte coordenadas esféricas em coordenadas cartesianas.
     */
    void ExplorerCamera::SphericalToCartesian() {
        cameraPos = camRadius * glm::dvec3(
            cos(camBeta) * sin(camAlpha),
            sin(camBeta),
            cos(camBeta) * cos(camAlpha)
        );
    }
}
