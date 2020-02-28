#include <iostream>

#define _USE_MATH_DEFINES
#include <cmath>

#include <tinyxml2/tinyxml2.h>

#include "Scene.h"
#include "window.h"

using namespace std;
using namespace tinyxml2;

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

    window::InitWindow(argv[0]);
    window::MainLoop();

    return 0;
}