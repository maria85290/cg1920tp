#include "Window.h"

namespace engine::window {
    Window* Window::instance = nullptr;

    Window::Window() : scene(Scene()), camera(nullptr), deltaTime(0) {}

    Window::~Window() {
        Window::instance = nullptr;

        delete this->camera;
        this->camera = nullptr;
    }

    void Window::InitWindow(char* programName) const {
        int argc = 1;
        char* argv2[] = {programName};

        glutInit(&argc, argv2);
        glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
        glutInitWindowPosition(100, 100);
        glutInitWindowSize(800, 800);
        glutCreateWindow(programName);

        glutDisplayFunc(glut_handlers::RenderScene);
        glutIdleFunc(glut_handlers::RenderScene);

        glutReshapeFunc(glut_handlers::HandleWindowChangeSize);

        glutKeyboardFunc(glut_handlers::HandleKeyPress);
        glutSpecialFunc(glut_handlers::HandleSpecialKeyPress);

        glutMouseFunc(glut_handlers::HandleMouseKeyPress);
        glutMotionFunc(glut_handlers::HandleMouseMovement);

        this->scene.InitGLSettings();
    }

    void Window::RenderScene() {
        ComputeDeltaTime();

        this->scene.ClearPreviousFrame();

        glLoadIdentity();
        this->camera->PositionInWorld();

        this->scene.Render();

        glutSwapBuffers();
    }

    void Window::MainLoop() const {
        if(this->camera == nullptr) {
            cerr << "Fatal error: no camera has been defined!" << endl;
            cerr << "Please define a camera by calling window->SetCamera() before attempting to enter GLUT's Main Loop." << endl;
            exit(-1);
        }

        glutMainLoop();
    }

    void Window::HandleWindowChangeSize(int w, int h) {
        // Prevent a divide by zero, when window is too short
        // (you cant make a window with zero width).
        if(h == 0)
            h = 1;

        double ratio = w * 1.0 / h;

        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();
        glViewport(0, 0, w, h);
        gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

        glMatrixMode(GL_MODELVIEW);
    }

    void Window::PrintInfo() const {
        printf("Vendor: %s\n", glGetString(GL_VENDOR));
        printf("Renderer: %s\n", glGetString(GL_RENDERER));
        printf("Version: %s\n", glGetString(GL_VERSION));
    }

    void Window::ComputeDeltaTime() {
        static int lastTime = 0;
        int currentTime = glutGet(GLUT_ELAPSED_TIME);

        this->deltaTime = currentTime - lastTime;
        lastTime = currentTime;
    }

    Scene& Window::GetScene() {
        return this->scene;
    }

    Camera* Window::GetCamera() {
        return this->camera;
    }

    void Window::SetCamera(Camera *camera) {
        this->camera = camera;
    }

    int Window::GetDeltaTime() {
        return this->deltaTime;
    }

    Window* Window::GetInstance() {
        if(instance == nullptr) {
            return instance = new Window;
        }

        return instance;
    }
}
