#ifndef CG_TP_ENGINE_SRC_WINDOW_CAMERAS_FPSCAMERA_H_
#define CG_TP_ENGINE_SRC_WINDOW_CAMERAS_FPSCAMERA_H_

#include "Camera.h"

#include <glm/vec3.hpp>

namespace engine::window::cameras {
    class FpsCamera: public Camera {
    private:
        double speed = 40.0;

        double lastMouseX;
        double lastMouseY;

        double yaw = 0;
        double pitch = 0;

        glm::dvec3 lookingAt;
        glm::dvec3 cameraPos = glm::dvec3(0, 0, -300);

        void SphericalToCartesian();
        glm::dvec3 ComputeForward();
        glm::dvec3 ComputeRight(glm::dvec3 forward);
        glm::dvec3 ComputeRight();
    public:
        FpsCamera() = default;
        ~FpsCamera() override;

        void InitCamera(Window* window, GLFWwindow* glfwWindow) override;
    	
        void PrintInfo() const override;

        void UpdatePosition() override;

        void HandleMouseKeyPress(int button, int action, int mods) override {}
        void HandleMouseMovement(double mouseX, double mouseY) override;

        void HandleScrollMovement(double xOffset, double yOffset) override;

        void HandleWindowChangeFocus(bool focused) override;
    };
}

#endif //CG_TP_ENGINE_SRC_WINDOW_CAMERAS_FPSCAMERA_H_
