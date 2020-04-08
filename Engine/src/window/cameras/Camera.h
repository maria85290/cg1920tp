#ifndef CG_TP_ENGINE_SRC_WINDOW_CAMERAS_CAMERA_H_
#define CG_TP_ENGINE_SRC_WINDOW_CAMERAS_CAMERA_H_

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>

namespace engine::window
{
    class Window;
}

namespace engine::window::cameras {
    /**
     * @brief Implementação de uma câmara 3D, e das suas Callbacks.
     */
    class Camera {
    protected:
        friend class ::engine::window::Window;

        Window* window;
    	GLFWwindow* glfwWindow;

    	/** Uma câmara define uma viewMatrix, que depois é aplicada antes de todo o processo de rendering pela função de renderização. */
    	glm::dmat4x4 viewMatrix;
    public:
        Camera() = default;
        virtual ~Camera() = default;

        virtual void InitCamera(Window* window, GLFWwindow* glfwWindow) {
            this->window = window;
            this->glfwWindow = glfwWindow;
        }
    	
        virtual void PrintInfo() = 0;

        /**
         * Responsável por reagir ao evento de uma tecla do teclado pressionada.
         * @param key
         * @param scanCode
         * @param action
         * @param mods
         */
        virtual void HandleKeyboardKeyPress(int key, int scanCode, int action, int mods) {}

        /**
         * Responsável por reagir a uma tecla do rato pressionada.
         * @param button
         * @param action
         * @param mods
         */
        virtual void HandleMouseKeyPress(int button, int action, int mods) {}

        /**
         * Responsável por reagir ao movimento do rato, desde que se encontre uma tecla do rato pressionada.
         * @param mouseX
         * @param mouseY
         */
        virtual void HandleMouseMovement(double mouseX, double mouseY) {}
    };
}

#endif //CG_TP_ENGINE_SRC_WINDOW_CAMERAS_CAMERA_H_
