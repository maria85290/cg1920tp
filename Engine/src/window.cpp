#include "window.h"

#include "glut.h"

namespace window {
    static Scene current_scene;

    void ChangeSize(int, int);
    void RenderScene();

    void InitWindow(char *programName) {
        int argc = 1;
        char *argv2[] = {programName};

        glutInit(&argc, argv2);
        glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
        glutInitWindowPosition(100, 100);
        glutInitWindowSize(800, 800);
        glutCreateWindow(programName);

        glutDisplayFunc(RenderScene);
        glutReshapeFunc(ChangeSize);

        // glutKeyboardFunc(processKeys);
        // glutSpecialFunc(processSpecialKeys);

        //  OpenGL settings
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
    }

    Scene& GetScene() {
        return current_scene;
    }

    void MainLoop() {
        glutMainLoop();
    }

    void ChangeSize(int w, int h) {
        // Prevent a divide by zero, when window is too short
        // (you cant make a window with zero width).
        if(h == 0)
            h = 1;

        // compute window's aspect ratio
        const float ratio = w * 1.0 / h;

        // Set the projection matrix as current
        glMatrixMode(GL_PROJECTION);
        // Load Identity Matrix
        glLoadIdentity();

        // Set the viewport to be the entire window
        glViewport(0, 0, w, h);

        // Set perspective
        gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

        // return to the model view matrix mode
        glMatrixMode(GL_MODELVIEW);
    }

    void RenderScene() {
        // clear buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // set the camera
        glLoadIdentity();

        gluLookAt(0.0, 4.0, 1.0,
                  0.0, 0.0, 0.0,
                  0.0, 1.0, 0.0);

        current_scene.Render();

        glutSwapBuffers();
    }

}
