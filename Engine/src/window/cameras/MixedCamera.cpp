#include "../../glut.h"
#include "../Window.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "MixedCamera.h"

using std::cout, std::endl;

namespace engine::window::cameras {
    MixedCamera::MixedCamera(vec3 center): center(center) {
        SphericalToCartesian();
    }

    void MixedCamera::PositionInWorld() {
        gluLookAt(cam.x, cam.y, cam.z,
                  center.x, center.y, center.z,
                  0, 1, 0);
    }

    void MixedCamera::HandleKeyPress(unsigned char key, int mouseX, int mouseY) {
        int deltaTime = Window::GetInstance()->GetDeltaTime();
        vec3 right = scale(ComputeRight(), 5.0/deltaTime);

        switch(key) {
            case 'w':
            case 'W':
                // Move forward

                camRadius -= 0.05 * deltaTime;

                if(camRadius < 5.0) {
                    camRadius = 5.0;
                }

                break;
            case 's':
            case 'S':
                // Move backward

                camRadius += 0.05 * deltaTime;

                break;
            case 'a':
            case 'A':
                // Move left

                this->center = {center.x - right.x, center.y - right.y, center.z - right.z};

                break;
            case 'd':
            case 'D':
                // Move right

                this->center = {center.x + right.x, center.y + right.y, center.z + right.z};

                break;
            default:
                break;
        }

        SphericalToCartesian();
    }

    /**
     * Callback do Glut para quando o utilizador clica (ou larga) uma tecla do rato.
     *
     * @param button
     * @param state
     * @param mouseX
     * @param mouseY
     */
    void MixedCamera::HandleMouseKeyPress(int button, int state, int mouseX, int mouseY) {
        switch(button) {
            case GLUT_LEFT_BUTTON:
                leftMousePressed = state == GLUT_DOWN;
                break;
            case GLUT_RIGHT_BUTTON:
                rightMousePressed = state == GLUT_DOWN;
                break;
            default:
                break;
        }

        lastMouseX = mouseX;
        lastMouseY = mouseY;
    }

    /**
     * Callback do Glut para quando um utilizador movimenta o rato, e uma das teclas está pressionada.
     *
     * @param mouseX
     * @param mouseY
     */
    void MixedCamera::HandleMouseMovement(int mouseX, int mouseY) {
        int deltaX = lastMouseX - mouseX;
        int deltaY = mouseY - lastMouseY;

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
    void MixedCamera::SphericalToCartesian() {
        cam.x = camRadius * cos(camBeta) * sin(camAlpha) + center.x;
        cam.y = camRadius * sin(camBeta) + center.y;
        cam.z = camRadius * cos(camBeta) * cos(camAlpha) + center.z;
    }

    vec3 MixedCamera::ComputeForward() {
        vec3 lookingAt = this->center;
        vec3 camPos = this->cam;

        return normalize({lookingAt.x - camPos.x,
                lookingAt.y - camPos.y,
                lookingAt.z - camPos.z});
    }

    vec3 MixedCamera::ComputeRight() {
        vec3 forward = ComputeForward();
        vec3 up = {0, 1, 0};

        return normalize(cross(forward, up));
    }
}
