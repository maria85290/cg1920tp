#ifndef CG_TP_ENGINE_SRC_WINDOW_WINDOW_H_
#define CG_TP_ENGINE_SRC_WINDOW_WINDOW_H_

#include "../Scene.h"
#include "cameras/Camera.h"

namespace engine::window {
    /**
     * @brief Singleton responsável pela configuração e manutenção de uma janela, capaz de renderizar cenas.
     */
    class Window {
    private:
        static Window* instance;

        int windowId;

        /**
         * A cena que está atualmente a ser desenhada.
         */
        Scene scene;

        /**
         * O tipo de câmara que está atualmente a ser utilizado para navegar o mundo.
         */
        cameras::Camera* camera;

        int deltaTime;
        int fps;

        Window();
        ~Window();

        void PrintInfo() const;
        void ComputeDeltaTime();
        void MeasureFps();
    public:
        static Window* GetInstance();

        void InitWindow(char* programName);
        void MainLoop() const;
        void DestroyWindow();

        Scene& GetScene();

        cameras::Camera* GetCamera();
        void SetCamera(cameras::Camera* camera);

        int GetDeltaTime();

        // Handlers de callbacks do GLUT
        void RenderScene();
        void HandleWindowChangeSize(int, int);
    };

    /**
     * Este namespace contém funções inline capazes de redirecionar as callbacks do GLUT para as funções membro
     * do singleton Window descrito acima.
     *
     * É ncessária a existência destes proxies pois GLUT é uma API C; logo não é compatível com objetos de C++.
     */
    namespace glut_handlers {
        inline void RenderScene() {
            Window::GetInstance()->RenderScene();
        }

        inline void HandleWindowChangeSize(int width, int height) {
            Window::GetInstance()->HandleWindowChangeSize(width, height);
        }

        inline void HandleKeyPress(unsigned char key, int mouseX, int mouseY) {
            cameras::Camera* camera = Window::GetInstance()->GetCamera();

            if(camera != nullptr)
                camera->HandleKeyPress(key, mouseX, mouseY);
        }

        inline void HandleSpecialKeyPress(int key, int mouseX, int mouseY) {
            cameras::Camera* camera = Window::GetInstance()->GetCamera();

            if(camera != nullptr)
                camera->HandleSpecialKeyPress(key, mouseX, mouseY);
        }

        inline void HandleMouseKeyPress(int button, int state, int x, int y) {
            cameras::Camera* camera = Window::GetInstance()->GetCamera();

            if(camera != nullptr)
                camera->HandleMouseKeyPress(button, state, x, y);
        }

        inline void HandleMouseMovement(int x, int y) {
            cameras::Camera* camera = Window::GetInstance()->GetCamera();

            if(camera != nullptr)
                camera->HandleMouseMovement(x, y);
        }
    }
}

#endif //CG_TP_ENGINE_SRC_WINDOW_WINDOW_H_
