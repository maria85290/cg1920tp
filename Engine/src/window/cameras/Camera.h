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

        virtual void PrintInfo() = 0;

        /**
         * Responsável por atualizar a posição da câmara no mundo.
         */
        virtual void UpdateCameraPosition() = 0;

        // GLUT Callbacks

        /**
         * Responsável por reagir ao evento de uma tecla do teclado pressionada.
         * @param key
         * @param mouseX
         * @param mouseY
         */
        virtual void HandleKeyPress(unsigned char key, int mouseX, int mouseY) {}
        /**
         * Responsável por reagir ao evento de uma tecla especial do teclado pressionada.
         * @param key
         * @param mouseX
         * @param mouseY
         */
        virtual void HandleSpecialKeyPress(int key, int mouseX, int mouseY) {}

        /**
         * Responsável por reagir a uma tecla do rato pressionada.
         * @param button
         * @param state
         * @param mouseX
         * @param mouseY
         */
        virtual void HandleMouseKeyPress(int button, int state, int mouseX, int mouseY) {}
        /**
         * Responsável por reagir ao movimento do rato, desde que se encontre uma tecla do rato pressionada.
         * @param mouseX
         * @param mouseY
         */
        virtual void HandleMouseMovement(int mouseX, int mouseY) {}
        /**
         * Responsável por reagir ao movimento do rato, quando não se encontra nenhuma tecla do rato pressionada.
         * @param mouseX
         * @param mouseY
         */
        virtual void HandlePassiveMouseMovement(int mouseX, int mouseY) {}
    };
}

#endif //CG_TP_ENGINE_SRC_WINDOW_CAMERAS_CAMERA_H_
