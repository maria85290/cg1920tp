#include "Window.h"

using std::string, std::cerr, std::endl;
using engine::window::cameras::Camera;

namespace engine::window {
    Window* Window::instance = nullptr;

    Window::Window() : scene(Scene()), camera(nullptr), deltaTime(0) {}

    Window::~Window() {
        Window::instance = nullptr;

        this->camera = nullptr;
    }

    void Window::InitWindow(char* programName) {
        int argc = 1;
        char* argv2[] = {programName};

        glutInit(&argc, argv2);
        glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
        glutInitWindowPosition(100, 100);
        glutInitWindowSize(800, 800);
        this->windowId = glutCreateWindow(programName);
        this->width = 800;
        this->height = 800;

        glewInit();

        glutDisplayFunc(glut_handlers::RenderScene);
        glutIdleFunc(glut_handlers::RenderScene);

        glutReshapeFunc(glut_handlers::HandleWindowChangeSize);
        glutEntryFunc(glut_handlers::HandleWindowEntry);

        glutKeyboardFunc(glut_handlers::HandleKeyPress);
        glutSpecialFunc(glut_handlers::HandleSpecialKeyPress);

        glutMouseFunc(glut_handlers::HandleMouseKeyPress);
        glutMotionFunc(glut_handlers::HandleMouseMovement);

        glutPassiveMotionFunc(glut_handlers::HandlePassiveMouseMovement);

        this->scene.InitGLSettings();
    }

    void Window::RenderScene() {
        ComputeDeltaTime();
        MeasureFps();

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

        PrintInfo();

        glutMainLoop();
    }

    void Window::HandleWindowChangeSize(int w, int h) {
        // Prevent a divide by zero, when window is too short
        // (you cant make a window with zero width).
        if(h == 0)
            h = 1;

        this->width = w;
        this->height = h;

        double ratio = w * 1.0 / h;

        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();
        glViewport(0, 0, w, h);
        gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

        glMatrixMode(GL_MODELVIEW);
    }

    void Window::HandleWindowEntry(int state) {
        focused = state == GLUT_ENTERED;
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

    void Window::MeasureFps()
    {
        static int timebase = 0;
        static int time = 0;
        static int frame = 0;

        frame++;
        time = glutGet(GLUT_ELAPSED_TIME);

        if(time - timebase > 1000)
        {
            fps = frame * 1000 / (time - timebase);
            timebase = time;
            frame = 0;

            glutSetWindowTitle((string("CG@DI-UM - FPS: ") + std::to_string(fps)).c_str());
        }
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

    void Window::DestroyWindow() {
        glutDestroyWindow(this->windowId);
    }

    Window* Window::GetInstance() {
        if(instance == nullptr) {
            return instance = new Window;
        }

        return instance;
    }
}
