#ifndef CG_TP_ENGINE_SRC_WINDOW_CAMERAS_EXPLORERCAMERA_H_
#define CG_TP_ENGINE_SRC_WINDOW_CAMERAS_EXPLORERCAMERA_H_

#include "Camera.h"

#include <glm/vec3.hpp>

namespace engine::window::cameras {
    class ExplorerCamera: public Camera {
    private:
        bool leftMousePressed = false;
        bool rightMousePressed = false;

        double lastMouseX;
        double lastMouseY;

        double camRadius = 100;
        double camAlpha = 0;
        double camBeta = 0;

        glm::dvec3 cameraPos;
        glm::dvec3 center;

        void SphericalToCartesian();
    public:
        explicit ExplorerCamera(glm::dvec3 center);

        void InitCamera(Window *window, GLFWwindow *glfwWindow) override;

        void PrintInfo() const override;

        void UpdatePosition() override;

        void HandleMouseKeyPress(int button, int action, int mods) override;
        void HandleMouseMovement(double mouseX, double mouseY) override;
    };
}

#endif //CG_TP_ENGINE_SRC_WINDOW_CAMERAS_EXPLORERCAMERA_H_
