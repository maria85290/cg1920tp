#include "FpsCamera.h"

#include "../../glut.h"
#include "../Window.h"

#define _USE_MATH_DEFINES
#include <math.h>

using std::cout, std::endl;

namespace engine::window::cameras {
    FpsCamera::FpsCamera() {
        glutSetCursor(GLUT_CURSOR_NONE);

        SphericalToCartesian();
    }

    FpsCamera::~FpsCamera() {
        glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
    }

    void FpsCamera::PrintInfo() {
        cout << "Use WASD to move the camera, and the mouse to change the yaw/pitch." << endl;
    }

    void FpsCamera::PositionInWorld() {
        gluLookAt(
            cameraPos.x, cameraPos.y, cameraPos.z,
            lookingAt.x, lookingAt.y, lookingAt.z,
            0, 1, 0
        );

        Window* window = Window::GetInstance();
        if(window->IsFocused()) {
            lastMouseX = window->GetWidth() / 2;
            lastMouseY = window->GetHeight() / 2;

            glutWarpPointer(lastMouseX, lastMouseY);
        }
    }

    void FpsCamera::HandleKeyPress(unsigned char key, int mouseX, int mouseY) {
        int deltaTime = Window::GetInstance()->GetDeltaTime();
        vec3 forward = ComputeForward();
        vec3 right = ComputeRight(forward);

        forward = scale(forward, 20.0/deltaTime);
        right = scale(right, 20.0/deltaTime);

        switch(key) {
            case 'w':
            case 'W':
                cameraPos = {cameraPos.x + forward.x, cameraPos.y + forward.y, cameraPos.z + forward.z};
                break;
            case 's':
            case 'S':
                cameraPos = {cameraPos.x - forward.x, cameraPos.y - forward.y, cameraPos.z - forward.z};
                break;
            case 'a':
            case 'A':
                cameraPos = {cameraPos.x - right.x, cameraPos.y - right.y, cameraPos.z - right.z};
                break;
            case 'd':
            case 'D':
                cameraPos = {cameraPos.x + right.x, cameraPos.y + right.y, cameraPos.z + right.z};
                break;
            default:
                break;
        }

        SphericalToCartesian();
    }

    void FpsCamera::HandleSpecialKeyPress(int key, int mouseX, int mouseY) {
        switch(key) {
            case GLUT_KEY_UP:
                this->HandleKeyPress('w', mouseX, mouseY);
                break;
            case GLUT_KEY_DOWN:
                this->HandleKeyPress('s', mouseX, mouseY);
                break;
            case GLUT_KEY_LEFT:
                this->HandleKeyPress('a', mouseX, mouseY);
                break;
            case GLUT_KEY_RIGHT:
                this->HandleKeyPress('d', mouseX, mouseY);
                break;
            default:
                break;
        }
    }

    void FpsCamera::HandlePassiveMouseMovement(int mouseX, int mouseY) {
        int deltaTime = Window::GetInstance()->GetDeltaTime() / 10;
        int deltaX = lastMouseX - mouseX;
        int deltaY = lastMouseY - mouseY;

        yaw += 0.001 * deltaX * deltaTime;
        yaw = fmod(yaw, 2 * M_PI); // camAlpha %= 360

        pitch += 0.001 * deltaY * deltaTime;

        if(pitch < -M_PI_2) {
            pitch = -M_PI_2 + 0.0001;
        } else if(pitch > M_PI_2) {
            pitch = M_PI_2 - 0.0001;
        }

        lastMouseX = mouseX;
        lastMouseY = mouseY;

        SphericalToCartesian();
    }

    void FpsCamera::SphericalToCartesian() {
        // LookingAt = ... + cameraPos
        // Isto mantém o vetor forward com tamanho de 1 unidade

        lookingAt.x = cos(pitch) * sin(yaw) + cameraPos.x;
        lookingAt.y = sin(pitch) + cameraPos.y;
        lookingAt.z = cos(pitch) * cos(yaw) + cameraPos.z;
    }

    vec3 FpsCamera::ComputeForward() {
        return normalize({lookingAt.x - cameraPos.x,
                          lookingAt.y - cameraPos.y,
                          lookingAt.z - cameraPos.z});
    }

    vec3 FpsCamera::ComputeRight(vec3 forward) {
        vec3 up = {0, 1, 0};

        return normalize(cross(forward, up));
    }

    vec3 FpsCamera::ComputeRight() {
        return this->ComputeRight(this->ComputeForward());
    }
}
