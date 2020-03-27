#ifndef CG_TP_ENGINE_SRC_WINDOW_CAMERAS_EXPLORERCAMERA_H_
#define CG_TP_ENGINE_SRC_WINDOW_CAMERAS_EXPLORERCAMERA_H_

#include "Camera.h"

namespace engine::window::cameras {
    class ExplorerCamera: public Camera {
    private:
        bool leftMousePressed = false;
        bool rightMousePressed = false;

        int lastMouseX;
        int lastMouseY;

        double camRadius = 100;
        double camAlpha = 0;
        double camBeta = 0;

        double camX;
        double camY;
        double camZ;

        void SphericalToCartesian();
    public:
        ExplorerCamera();

        void PositionInWorld() override;

        void HandleKeyPress(unsigned char, int, int) override {}
        void HandleSpecialKeyPress(int, int, int) override {}

        void HandleMouseKeyPress(int button, int state, int mouseX, int mouseY) override;
        void HandleMouseMovement(int mouseX, int mouseY) override;
    };
}

#endif //CG_TP_ENGINE_SRC_WINDOW_CAMERAS_EXPLORERCAMERA_H_
