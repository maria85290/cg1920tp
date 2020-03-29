#ifndef CG_TP_ENGINE_SRC_WINDOW_CAMERAS_FPSCAMERA_H_
#define CG_TP_ENGINE_SRC_WINDOW_CAMERAS_FPSCAMERA_H_

#include <Common/vectors.h>
#include "Camera.h"

namespace engine::window::cameras {
    class FpsCamera: public Camera {
    private:
        int lastMouseX;
        int lastMouseY;

        double yaw = 0;
        double pitch = 0;

        vec3 lookingAt;
        vec3 cameraPos = {0, 0, -300};

        void SphericalToCartesian();
        vec3 ComputeForward();
        vec3 ComputeRight(vec3 forward);
        vec3 ComputeRight();
    public:
        FpsCamera();
        ~FpsCamera() override;

        void PrintInfo() override;

        void PositionInWorld() override;

        void HandleKeyPress(unsigned char key, int mouseX, int mouseY) override;
        void HandleSpecialKeyPress(int key, int mouseX, int mouseY) override;

        void HandleMouseMovement(int mouseX, int mouseY) override {}
        void HandleMouseKeyPress(int button, int state, int mouseX, int mouseY) override {}
        void HandlePassiveMouseMovement(int mouseX, int mouseY) override;
    };
}

#endif //CG_TP_ENGINE_SRC_WINDOW_CAMERAS_FPSCAMERA_H_
