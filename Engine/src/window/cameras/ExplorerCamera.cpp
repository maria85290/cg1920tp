#include "../../glut.h"
#include "../Window.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "ExplorerCamera.h"

namespace engine::window::cameras {
    ExplorerCamera::ExplorerCamera() {
        SphericalToCartesian();
    }

    void ExplorerCamera::PositionInWorld() {
        gluLookAt(camX, camY, camZ,
                  0, 0, 0,
                  0, 1, 0);
    }

    /**
     * Callback do Glut para quando o utilizador clica (ou larga) uma tecla do rato.
     *
     * @param button
     * @param state
     * @param mouseX
     * @param mouseY
     */
    void ExplorerCamera::HandleMouseKeyPress(int button, int state, int mouseX, int mouseY) {
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
    void ExplorerCamera::HandleMouseMovement(int mouseX, int mouseY) {
        int deltaTime = Window::GetInstance()->GetDeltaTime();

        int deltaX = lastMouseX - mouseX;
        int deltaY = mouseY - lastMouseY;

        if(leftMousePressed) {
            camAlpha += 0.001 * deltaX * deltaTime;
            camAlpha = fmod(camAlpha, 2 * M_PI); // camAlpha %= 360

            camBeta += 0.001 * deltaY * deltaTime;

            if(camBeta < -M_PI_2) {
                camBeta = -M_PI_2;
            } else if(camBeta > M_PI_2) {
                camBeta = M_PI_2;
            }
        } else if(rightMousePressed) {
            camRadius -= 0.05 * deltaY * deltaTime;

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
        camX = camRadius * cos(camBeta) * sin(camAlpha);
        camY = camRadius * sin(camBeta);
        camZ = camRadius * cos(camBeta) * cos(camAlpha);
    }
}
