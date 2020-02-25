#include <iostream>
#define _USE_MATH_DEFINES

#include <tinyxml2/tinyxml2.h>

#include "Scene.cpp"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Engine requer exatamente 1 argumento, o ficheiro de configuração XML." << endl;
        cerr << "Uso ./engine <file.xml>" << endl;
        return 1;
    }

    Scene scene = Scene();
    tinyxml2::XMLDocument config;

    tinyxml2::XMLError result = config.LoadFile(argv[1]);

    if (result != tinyxml2::XML_SUCCESS) {
        cerr << "Ocorreu um erro na leitura do ficheiro de configuração XML fornecido." << endl;
        return 1;
    }

    tinyxml2::XMLNode* root = config.FirstChild();

    if (strcmp(root->Value(), "scene") != 0) {
        cerr << "Esperado valor 'scene', obtido '" << root->Value() << "'" << endl;
        return 1;
    }

    if (root->NoChildren()) {
        cout << "Não contêm models." << endl;
        return 0;
    }

    tinyxml2::XMLNode* model = root->FirstChild();

    while(model != nullptr) {
        tinyxml2::XMLElement* element = model->ToElement();

        if (strcmp(model->Value(), "model") != 0) {
            cerr << "Esperado valor 'model', obtido '" << model->Value() << "'" << endl;
            return 1;
        }

        const char *file = element->Attribute("file");

        if (file == nullptr) {
            cerr << "Não existe campo 'file'." << endl;
            return 0;
        }

        scene.addModel(Model(file));
        model = model->NextSibling();
    }

    list<Model> models = scene.getModels_();
    for (auto & model_i : models){
        cout << model_i.GetFile() << endl;
    }

    return 0;
}
