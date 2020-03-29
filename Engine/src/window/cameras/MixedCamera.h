#ifndef CG_TP_ENGINE_SRC_WINDOW_CAMERAS_EXPLORERCAMERA_H_
#define CG_TP_ENGINE_SRC_WINDOW_CAMERAS_EXPLORERCAMERA_H_

#include <Common/vectors.h>
#include "Camera.h"

namespace engine::window::cameras {
    class MixedCamera: public Camera {
    private:
        bool leftMousePressed = false;
        bool rightMousePressed = false;

        int lastMouseX;
        int lastMouseY;

        double camRadius = 100;
        double camAlpha = 0;
        double camBeta = 0;

        vec3 cam;

        vec3 center;

        void SphericalToCartesian();
        vec3 ComputeForward();
        vec3 ComputeRight();
    public:
        explicit MixedCamera(vec3 center);

        void PositionInWorld() override;

        void HandleKeyPress(unsigned char key, int mouseX, int mouseY) override;
        void HandleSpecialKeyPress(int key, int mouseX, int mouseY) override {}

        void HandleMouseKeyPress(int button, int state, int mouseX, int mouseY) override;
        void HandleMouseMovement(int mouseX, int mouseY) override;
    };
}

#endif //CG_TP_ENGINE_SRC_WINDOW_CAMERAS_EXPLORERCAMERA_H_
