#include <iostream>

#include "Model.h"

#include "Models.h"

using std::cerr, std::endl;
using tinyxml2::XMLNode, tinyxml2::XMLElement;

namespace engine::entities {
    bool Models::ParseXml(XMLNode *modelsNode) {
        XMLNode *node = modelsNode->FirstChild();

        while(node != nullptr) {
            XMLElement *element = node->ToElement();

            if(strcmp("model", node->Value()) != 0) {
                cerr << "Esperado valor 'model', obtido '" << node->Value() << "'" << endl;
                return false;
            }

            const char *file = element->Attribute("file");

            if(file == nullptr) {
                cerr << "Não existe campo 'file'." << endl;
                return false;
            }

            this->AddModel(new Model(file));

            node = node->NextSibling();
        }

        return true;
    }

    void Models::Render() const {
        for(const Model *model : models) {
            model->Render();
        }
    }
}