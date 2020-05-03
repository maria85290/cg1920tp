#ifndef CG_TP_ENGINE_SRC_WINDOW_WINDOW_H_
#define CG_TP_ENGINE_SRC_WINDOW_WINDOW_H_

#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "../scene/Scene.h"

#include "cameras/Camera.h"
#include "input/Keyboard.h"

namespace engine::window {
    /**
     * @brief Classe responsável pela configuração e manutenção de uma janela, capaz de renderizar cenas.
     */
    class Window {
    private:
        friend class cameras::Camera;

        GLFWwindow* glfwWindow = nullptr;

        std::string title;

        int width = 1280;
        int height = 720;

        bool focused = false;

        /**
         * O tipo de câmara que está atualmente a ser utilizado para navegar o mundo.
         */
        cameras::Camera* camera = nullptr;

        /**
         * A cena que está atualmente a ser desenhada.
         */
        scene::Scene* scene = nullptr;

        double deltaTime = 0;
        int fps = 0;

        void PrintInfo() const;
        void ComputeDeltaTime();
        void MeasureFps();
        void RenderAxis() const;

        static void DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
    public:
        Window(const char* title, int width, int height);
        ~Window();

        bool CreateWindow();
        void MainLoop();

        /** Obtém a câmara que está a ser utilizada para o movimento nesta janela. */
        cameras::Camera* GetCamera() const { return camera; }
        /** Define uma nova câmara que está a ser utilizada para o movimento nesta janela. */
        void SetCamera(cameras::Camera* camera)
        {
            if(this->glfwWindow == nullptr)
                throw std::runtime_error("Não é possível inicializar a câmara sem inicializar a janela primeiro!");

	        this->camera = camera;
            this->camera->InitCamera(this, this->glfwWindow);
        }

        /** Obtém a cena que vai ser renderizada nesta janela. */
        scene::Scene* GetScene() const { return scene; }

        /** Define qual a cena que vai ser renderizada nesta janela. */
        void SetScene(scene::Scene* scene)
        {
            this->scene = scene;
        }

        double GetDeltaTime() const { return deltaTime; }
        /** Retorna o comprimento da janela. */
        int GetWidth() const { return width; }
        /** Retorna a altura da janela. */
        int GetHeight() const { return height; }
        /** Retorna se a janela está em foco ou não. */
        bool IsFocused() const { return focused; }

        /** Renderiza uma frame. */
        void ProcessFrame();
        /** Callback do glfw para quando a janela muda de tamanho. */
        void HandleFramebufferSizeChange(int width, int height);

        void HandleWindowChangeFocus(bool focused) {
            this->focused = focused;
        }

        void HandleKeyboardKeyPress(int key, int scanCode, int action, int mods);
    };

    /**
     * Este namespace contém funções inline capazes de redirecionar as callbacks do GLFW para as funções membro
     * da classe Window descrita acima.
     *
     * É ncessária a existência destes proxies pois GLFW é uma API C; logo não é compatível com objetos de C++.
     */
    namespace callback_handlers {
        inline void HandleFramebufferSizeChange(GLFWwindow* glfwWindow, int width, int height) {
            Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

            window->HandleFramebufferSizeChange(width, height);
        }

        inline void HandleKeyboardKeyPress(GLFWwindow* glfwWindow, int key, int scanCode, int action, int mods) {
            Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
            cameras::Camera* camera = window->GetCamera();

            ::engine::window::input::Keyboard::HandleKeyPress(key, scanCode, action, mods);
            window->HandleKeyboardKeyPress(key, scanCode, action, mods);
            camera->HandleKeyboardKeyPress(key, scanCode, action, mods);
        }

        inline void HandleMouseKeyPress(GLFWwindow* glfwWindow, int button, int action, int mods) {
            Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
            cameras::Camera* camera = window->GetCamera();

            camera->HandleMouseKeyPress(button, action, mods);
        }

        inline void HandleMouseMovement(GLFWwindow* glfwWindow, double x, double y) {
            Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
            cameras::Camera* camera = window->GetCamera();

            camera->HandleMouseMovement(x, y);
        }

        inline void HandleScrollMovement(GLFWwindow* glfwWindow, double xOffset, double yOffset) {
            Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
            cameras::Camera* camera = window->GetCamera();

            camera->HandleScrollMovement(xOffset, yOffset);
        }

        inline void HandleWindowChangeFocus(GLFWwindow* glfwWindow, int focused) {
            Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
            cameras::Camera* camera = window->GetCamera();

            window->HandleWindowChangeFocus(focused == GLFW_TRUE);
            camera->HandleWindowChangeFocus(focused == GLFW_TRUE);
        }
    }
}

#endif //CG_TP_ENGINE_SRC_WINDOW_WINDOW_H_
