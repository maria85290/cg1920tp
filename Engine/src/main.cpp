#include <iostream>

#define _USE_MATH_DEFINES

#include <cmath>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#include <tinyxml2/tinyxml2.h>

#include "Scene.h"

#include "window.h"

using namespace std;
using namespace tinyxml2;

Scene scene;

float angle = 0;




void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if(h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;

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

void render() {
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();

    gluLookAt(0.0, 4.0, 1.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glBegin(GL_LINES);

    glColor3f(0.5, 0, 0);
    glVertex3f(-100, 0, 0);
    glVertex3f(0, 0, 0);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(100, 0, 0);

    glColor3f(0, 0.5, 0);
    glVertex3f(0, -100, 0);
    glVertex3f(0, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 100, 0);

    glColor3f(0, 0, 0.5);
    glVertex3f(0, 0, -100);
    glVertex3f(0, 0, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 100);

    glEnd();


    glPolygonMode(GL_FRONT, GL_LINE); // Desenhar linhas em vez de encher os triângulos com cor

    glColor3f(1, 0, 0);

    // permite o movimento do teclado
   
	glRotatef(angle, 0, 0, 1);

    scene.Render();

    glutSwapBuffers();
}


void  keyboard_events(unsigned char k, int mouseX, int mouseY) {
    if (k = 'q') {
        angle = fmod((angle + 1), 180);
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        cerr << "Engine requer exatamente 1 argumento, o ficheiro de configuração XML." << endl;
        cerr << "Uso ./engine <file.xml>" << endl;
        return 1;
    }

    XMLDocument document;

    if(document.LoadFile(argv[1]) != XML_SUCCESS) {
        cerr << "Ocorreu um erro na leitura do ficheiro de configuração XML fornecido." << endl;
        return 1;
    }

    XMLNode *root = document.FirstChild();

    if(strcmp("scene", root->Value()) != 0) {
        cerr << "Esperado valor 'scene', obtido '" << root->Value() << "'" << endl;
        return 1;
    }

    if(root->NoChildren()) {
        cout << "Não contêm models." << endl;
        return 1;
    }

    XMLNode *model = root->FirstChild();

    Scene& scene = window::GetScene();

    while(model != nullptr) {
        XMLElement *element = model->ToElement();

        if(strcmp("model", model->Value()) != 0) {
            cerr << "Esperado valor 'model', obtido '" << model->Value() << "'" << endl;
            return 1;
        }

        const char *file = element->Attribute("file");

        if(file == nullptr) {
            cerr << "Não existe campo 'file'." << endl;
            return 1;
        }

        scene.AddModel(Model(file));
        model = model->NextSibling();
    }

    // init GLUT and the window
    argc = 1;
    char *argv2[] = {argv[0]};
    glutInit(&argc, argv2);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG@DI-UM");

    // Required callback registry
    glutDisplayFunc(render);
    glutReshapeFunc(changeSize);

    // Callback registration for keyboard processing
    glutKeyboardFunc(keyboard_events);
    // glutSpecialFunc(processSpecialKeys);

    //  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // enter GLUT's main cycle
    glutMainLoop();


    return 0;
}
