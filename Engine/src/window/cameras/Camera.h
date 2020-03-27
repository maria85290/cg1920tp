#ifndef CG_TP_ENGINE_SRC_WINDOW_CAMERAS_CAMERA_H_
#define CG_TP_ENGINE_SRC_WINDOW_CAMERAS_CAMERA_H_


namespace engine::window::cameras {
    /**
     * @brief Implementação de uma câmara 3D, e das suas Callbacks.
     */
    class Camera {
    public:
        Camera() = default;
        virtual ~Camera() = default;

        virtual void PositionInWorld() = 0;

        // GLUT Callbacks

        virtual void HandleKeyPress(unsigned char, int, int) {}
        virtual void HandleSpecialKeyPress(int, int, int) {}

        virtual void HandleMouseKeyPress(int button, int state, int mouseX, int mouseY) {}
        virtual void HandleMouseMovement(int mouseX, int mouseY) {}
    };
}

#endif //CG_TP_ENGINE_SRC_WINDOW_CAMERAS_CAMERA_H_
