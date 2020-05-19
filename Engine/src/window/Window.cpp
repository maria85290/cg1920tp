#include "Window.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glad/glad.h>

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../util/Settings.h"

using std::string, std::cerr, std::endl;
using std::unique_ptr;
using engine::window::cameras::Camera;
using tinyxml2::XMLDocument;

extern unique_ptr<XMLDocument> ReadSceneFile(const char*);

namespace engine::window {
    Window::Window(const char* title, int width, int height):
    title(title), width(width), height(height)
    {}

    Window::~Window() {
        glfwSetWindowUserPointer(this->glfwWindow, nullptr);
        glfwDestroyWindow(this->glfwWindow);
        this->glfwWindow = nullptr;
    }

    bool Window::CreateWindow() {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
        glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

        glfwWindowHint(GLFW_FOCUSED, GLFW_FALSE);

#ifndef NDEBUG
        if (glfwExtensionSupported("GL_ARB_debug_output") == GLFW_TRUE) {
            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
        }
#endif

        this->glfwWindow = glfwCreateWindow(this->width, this->height, this->title.c_str(), nullptr, nullptr);

        if(!this->glfwWindow) {
            return false;
        }

        glfwSetWindowUserPointer(this->glfwWindow, this);

        glfwSetFramebufferSizeCallback(this->glfwWindow, callback_handlers::HandleFramebufferSizeChange);
        glfwSetKeyCallback(this->glfwWindow, callback_handlers::HandleKeyboardKeyPress);
        glfwSetMouseButtonCallback(this->glfwWindow, callback_handlers::HandleMouseKeyPress);
        glfwSetCursorPosCallback(this->glfwWindow, callback_handlers::HandleMouseMovement);
        glfwSetScrollCallback(this->glfwWindow, callback_handlers::HandleScrollMovement);
        glfwSetWindowFocusCallback(this->glfwWindow, callback_handlers::HandleWindowChangeFocus);

        glfwMakeContextCurrent(this->glfwWindow);
        glfwSwapInterval(1);

        gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        if(!gladLoadGL()) {
            cerr << "Failed to initialize OpenGL Context!" << endl;
            return false;
        }

#ifndef NDEBUG
        if (glfwExtensionSupported("GL_ARB_debug_output") == GLFW_TRUE) {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(Window::DebugCallback, nullptr);
        }

        Settings::Set("debug", "true");
#endif

        return true;
    }

    void Window::MainLoop() {
        if(this->glfwWindow == nullptr) {
            throw std::runtime_error("A janela ainda não foi criada!");
        }

    	if(this->scene == nullptr)
    	{
            throw std::runtime_error("Não foi definida uma cena a renderizar!");
    	}

    	if(this->camera == nullptr)
    	{
            throw std::runtime_error("Não foi definida uma câmara para navegar a cena!");
    	}

        glfwMakeContextCurrent(this->glfwWindow);

    	this->HandleFramebufferSizeChange(this->width, this->height);
    	this->HandleWindowChangeFocus(glfwGetWindowAttrib(this->glfwWindow, GLFW_FOCUSED) == GLFW_TRUE);

        this->scene->InitGLSettings();

        this->PrintInfo();
        this->camera->PrintInfo();

        while(!glfwWindowShouldClose(this->glfwWindow)) {
            this->ProcessFrame();
        }
    }

    void Window::ProcessFrame() {
        // Compute some values required for updating the scene
        this->ComputeDeltaTime();
        this->MeasureFps();

        // Process all events in queue
        glfwPollEvents();

        // Update the scene elements
        this->camera->UpdatePosition();
        this->scene->Update(deltaTime);

        // Render the next frame
        this->scene->ClearPreviousFrame();

        glLoadIdentity();
        glMultMatrixd(glm::value_ptr(this->camera->viewMatrix)); // Set camera position in world

        if(Settings::Contains("debug"))
            this->RenderAxis();
        this->scene->Render();

        // Swap buffers
        glfwSwapBuffers(this->glfwWindow);
    }

    void Window::PrintInfo() const {
        printf("Vendor: %s\n", glGetString(GL_VENDOR));
        printf("Renderer: %s\n", glGetString(GL_RENDERER));
        printf("Version: %s\n", glGetString(GL_VERSION));
    }

    void Window::ComputeDeltaTime() {
        static double lastTime = 0;
        double currentTime = glfwGetTime();

        this->deltaTime = currentTime - lastTime;
        lastTime = currentTime;
    }

    void Window::MeasureFps()
    {
        static double timebase = 0;
        static double time = 0;
        static int frame = 0;

        frame++;
        time = glfwGetTime();

        if(time - timebase > 1.0) {
            fps = (int) round(frame / (time - timebase));
            timebase = time;
            frame = 0;

            const string title = string(this->title) + " - FPS: " + std::to_string(fps);
            glfwSetWindowTitle(this->glfwWindow, title.c_str());
        }
    }

    void Window::RenderAxis() const {
        static const float axisSize = 100;

        glBegin(GL_LINES);

        glColor3f(1, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(axisSize, 0, 0);

        glColor3f(0, 1, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, axisSize, 0);

        glColor3f(0, 0, 1);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, axisSize);

        glEnd();

        glColor3f(1.0, 1.0, 1.0);
    }

    void Window::HandleFramebufferSizeChange(int width, int height) {
        if(height == 0)
            height = 1;

        this->width = width;
        this->height = height;

        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

        glViewport(0, 0, width, height);

        glm::dmat4 projectionMatrix = glm::perspective(glm::radians(45.0), double(width) / double(height), 0.1, 5000.0);
        glMultMatrixd(glm::value_ptr(projectionMatrix));

        glMatrixMode(GL_MODELVIEW);
    }

    void Window::HandleKeyboardKeyPress(int key, int scanCode, int action, int mods) {
        if(key == GLFW_KEY_F1 && action == GLFW_PRESS) {
            if(glIsEnabled(GL_CULL_FACE))
                glDisable(GL_CULL_FACE);
            else
                glEnable(GL_CULL_FACE);
        }

        if(key == GLFW_KEY_F2 && action == GLFW_PRESS) {
            int polygonMode[2];
            glGetIntegerv(GL_POLYGON_MODE, polygonMode);

            if(polygonMode[0] == GL_FILL)
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        if(key == GLFW_KEY_F3 && action == GLFW_PRESS) {
            if(Settings::Contains("debug")) {
                Settings::Delete("debug");
            } else {
                Settings::Set("debug", "true");
            }
        }

        if(key == GLFW_KEY_F5 && action == GLFW_PRESS) {
            this->ReloadScene();
        }
    }

    void Window::ReloadScene() {
        // Delete the old scene and caches
        delete this->scene;
        ModelMesh::GetCache().Clear();
        Texture::GetCache().Clear();
        scene::lighting::Light::ResetLightNo();

        this->scene = new scene::Scene;

        // Find out if the scene file exists
        auto root = ReadSceneFile(this->sceneFile.c_str());

        // Parse the scene file
        this->scene->ParseXml(root->FirstChild());
    }

	void APIENTRY Window::DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
	{
        fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
            type, severity, message);
	}
}
