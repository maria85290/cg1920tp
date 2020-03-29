#include <iostream>

#include "Model.h"

#include "Models.h"

using std::cerr, std::endl;
using tinyxml2::XMLNode, tinyxml2::XMLElement, tinyxml2::XMLComment;

namespace engine::entities {
    bool Models::ParseXml(XMLNode *modelsNode) {
        XMLNode *node = modelsNode->FirstChild();

        while(node != nullptr) {
            if(dynamic_cast<const XMLComment*>(node)) {
                node = node->NextSibling();
                continue;
            }

            XMLElement *element = node->ToElement();

            if(strcmp("model", node->Value()) != 0) {
                cerr << "Esperado valor 'model', obtido '" << node->Value() << "'" << endl;
                return false;
            }

            const Model* model = Model::LoadModel(element);

            if(model == nullptr) {
                return false;
            }

            this->AddModel(model);

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