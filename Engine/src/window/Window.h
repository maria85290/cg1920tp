#ifndef CG_TP_ENGINE_SRC_WINDOW_WINDOW_H_
#define CG_TP_ENGINE_SRC_WINDOW_WINDOW_H_

#include <string>

#include "../Scene.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "cameras/Camera.h"

namespace engine::window {
    /**
     * @brief Classe responsável pela configuração e manutenção de uma janela, capaz de renderizar cenas.
     */
    class Window {
    private:
        friend class Camera;

        GLFWwindow* glfwWindow = nullptr;

        std::string title;

        int width = 1280;
        int height = 720;

        /**
         * O tipo de câmara que está atualmente a ser utilizado para navegar o mundo.
         */
        cameras::Camera* camera = nullptr;

        /**
         * A cena que está atualmente a ser desenhada.
         */
        Scene* scene = nullptr;

        double deltaTime = 0;
        int fps = 0;

        void PrintInfo() const;
        void ComputeDeltaTime();
        void MeasureFps();

        static void DebugCallback(gl::GLenum source, gl::GLenum type, gl::GLuint id, gl::GLenum severity, gl::GLsizei length, const gl::GLchar* message, const void* userParam);
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
        Scene* GetScene() const { return scene; }

        /** Define qual a cena que vai ser renderizada nesta janela. */
        void SetScene(Scene* scene)
        {
            this->scene = scene;
        }

        double GetDeltaTime() const { return deltaTime; }
        /** Retorna o comprimento da janela. */
        int GetWidth() const { return width; }
        /** Retorna a altura da janela. */
        int GetHeight() const { return height; }

        /** Renderiza uma frame. */
        void RenderFrame();
        /** Callback do glut para quando a janela muda de tamanho. */
        void HandleFramebufferSizeChange(int width, int height);
    };

    /**
     * Este namespace contém funções inline capazes de redirecionar as callbacks do GLUT para as funções membro
     * do singleton Window descrito acima.
     *
     * É ncessária a existência destes proxies pois GLUT é uma API C; logo não é compatível com objetos de C++.
     */
    namespace callback_handlers {
        inline void HandleFramebufferSizeChange(GLFWwindow* glfwWindow, int width, int height) {
            Window* window = (Window*) glfwGetWindowUserPointer(glfwWindow);
            window->HandleFramebufferSizeChange(width, height);
        }

        inline void HandleKeyboardKeyPress(GLFWwindow* glfwWindow, int key, int scanCode, int action, int mods) {
            Window* window = (Window*) glfwGetWindowUserPointer(glfwWindow);
            cameras::Camera* camera = window->GetCamera();

            camera->HandleKeyboardKeyPress(key, scanCode, action, mods);
        }

        inline void HandleMouseKeyPress(GLFWwindow* glfwWindow, int button, int action, int mods) {
            Window* window = (Window*) glfwGetWindowUserPointer(glfwWindow);
            cameras::Camera* camera = window->GetCamera();

            camera->HandleMouseKeyPress(button, action, mods);
        }

        inline void HandleMouseMovement(GLFWwindow* glfwWindow, double x, double y) {
            Window* window = (Window*) glfwGetWindowUserPointer(glfwWindow);
            cameras::Camera* camera = window->GetCamera();

            camera->HandleMouseMovement(x, y);
        }
    }
}

#endif //CG_TP_ENGINE_SRC_WINDOW_WINDOW_H_
