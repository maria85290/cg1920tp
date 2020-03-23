#include <iostream>
#include <cstdio>
#include "glut.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <tinyxml2/tinyxml2.h>

#include "Scene.h"

#include "window.h"

using namespace std;
using namespace tinyxml2;
using namespace entities;

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

    Scene& scene = window::GetScene();
    scene.ParseXml(root);
	
    window::InitWindow(argv[0]);
    window::MainLoop();

    return 0;
}
