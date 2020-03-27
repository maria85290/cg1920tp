#include <iostream>
#include <cstdio>
#include "glut.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <tinyxml2/tinyxml2.h>

#include "Scene.h"

#include "window/Window.h"
#include "window/cameras/ExplorerCamera.h"

using namespace engine;
using namespace std;
using namespace tinyxml2;
using engine::window::Window;
using engine::window::cameras::ExplorerCamera;

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

    Window* window = Window::GetInstance();

    Scene& scene = window->GetScene();
    if(!scene.ParseXml(root)) {
        return -1;
    }
	
    window->InitWindow(argv[0]);
    window->SetCamera(new ExplorerCamera);
    window->MainLoop();

    return 0;
}
